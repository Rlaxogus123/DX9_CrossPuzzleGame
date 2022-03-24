#include "DXUT.h"
#include "Include.h"

void GamePlay::CreateTile()
{
	ifstream file(L"res/tileData.txt");
	char buff[3];

	file.getline(buff,3);
	file.getline(buff,3);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			tile = new Tile;
			tile->_layer = -1;
			tile->_visible = true;
			tile->_position = { (float)(200 + x * 32),(float)(200 + y * 32) };

			file.getline(buff, 3);
			if (atoi(buff) == 1) purpose++;
			tile->count = atoi(buff);

			tile->x = x;
			tile->y = y;

			tilelist.push_back(tile);
		}
	}
}

void GamePlay::DeleteTile()
{
	for (auto it : tilelist)
	{
		it->_sprite->Release();
		delete it;
	}
	tilelist.clear();
}

void GamePlay::DeleteFont()
{
	for (auto it : fontlist)
	{
		it->_font->Release();
		delete it;
	}
	fontlist.clear();
}

void GamePlay::verticalReadLine()
{
	for (int j = 0; j < sizeY; j++)
	{
		int count = 0;
		vector<int> countlist;

		Tile* curTile = nullptr;

		for (int i = 0; i < sizeX; i++)
		{
			curTile = GamePlay::GetIns()->tilelist[i + (j * sizeX)];
			if (curTile->count)
			{
				count++;
				continue;
			}
			else
			{
				if (count > 0) countlist.push_back(count);
				count = 0;
				continue;
			}
		}
		if (count > 0) countlist.push_back(count);

		if (countlist.size() == 0)
		{
			Font* countFont = new Font;
			countFont->_position = { (float)(160),190 + ((float)j * 32) };
			countFont->CreateMyfont(1.2, 700);
			countFont->SetString("0");

			fontlist.push_back(countFont);
		}
		for (int i = 0; i < countlist.size(); i++)
		{
			Font* countFont = new Font;
			countFont->_position = { (float)(160 - (32 * i)),190 + ((float)j * 32) };
			countFont->CreateMyfont(1.2, 700);
			char buff[5];
			sprintf(buff, "%d", countlist[countlist.size() - i - 1]);
			countFont->SetString(buff);
			fontlist.push_back(countFont);
		}
	}
}

void GamePlay::horizontalReadLine()
{
	for (int x = 0; x < sizeX; x++)
	{
		int count = 0;
		vector<int> countlist;

		Tile* curTile = nullptr;

		for (int y = 0; y < sizeY; y++)
		{
			curTile = GamePlay::GetIns()->tilelist[x + (y * sizeX)];
			if (curTile->count)
			{
				count++;
				continue;
			}
			else
			{
				if (count > 0) countlist.push_back(count);
				count = 0;
				continue;
			}
		}
		if (count > 0) countlist.push_back(count);

		if (countlist.size() == 0)
		{
			Font* countFont = new Font;
			countFont->_position = { (float)(200 + ((float)x * 32)), 158 };
			countFont->CreateMyfont(1.2, 700);
			countFont->SetString("0");

			fontlist.push_back(countFont);
		}
		for (int i = 0; i < countlist.size(); i++)
		{
			Font* countFont = new Font;
			countFont->_position = { (float)(198 + ((float)x * 32)), 158 - ((float)i * 32) };
			countFont->CreateMyfont(1.2, 700);
			char buff[5];
			sprintf(buff, "%d", countlist[countlist.size() - i - 1]);
			countFont->SetString(buff);
			fontlist.push_back(countFont);
		}
	}
}

bool GamePlay::isClick(RECT r)
{
	if (r.left < Director::GetIns()->GetMousePos().x
		&& r.right > Director::GetIns()->GetMousePos().x
		&& r.top < Director::GetIns()->GetMousePos().y
		&& r.bottom > Director::GetIns()->GetMousePos().y)
	{
		return true;
	}
	return false;
}

bool GamePlay::isWorldClick(RECT r)
{
	vec2 absPos;
	absPos.x = (Camera::GetIns()->_camPos.x - ScreenWidth / 2) + Director::GetIns()->GetMousePos().x;
	absPos.y = (Camera::GetIns()->_camPos.y - ScreenHeight / 2) + Director::GetIns()->GetMousePos().y;

	if (r.left < absPos.x
		&& r.right > absPos.x
		&& r.top < absPos.y
		&& r.bottom > absPos.y)
	{
		return true;
	}
	return false;
}

void GamePlay::InitGamePlay()
{
	ifstream in("res/tileData.txt");
	if (in.is_open())
	{
		char buff[255];
		in.getline(buff, 255);
		sizeX = atoi(buff);
		in.getline(buff, 255);
		sizeY = atoi(buff);
	}
	else
	{
		Director::GetIns()->ChangeScene(new GameScene);
		return;
	}

	purpose = 0;
	curpose = 0;
	errorpose = 0;

	CreateTile();
	verticalReadLine();
	horizontalReadLine();

	gameclear = false;
	cheat = false;

	backEditor = new Sprite(L"backEditor.png");
	backEditor->_position = { 100,970 };
	backEditor->_isUI = true;
	really = false;

	start = new Sprite(L"Clear.png");
	start->_position = { 700,800 };
	start->_isUI = true;
	start->_color.a = -1;

	size = new Font;
	size->_isUI = true;
	size->_color = color(1, 1, 0, 1);
	size->_position = { 0,60 };
	size->CreateMyfont(2, 900);
}

void GamePlay::UpdateGamePlay()
{
	char buff[100];
	sprintf(buff, "Size : %dx%d", sizeX, sizeY);
	size->SetString(buff);

	if (purpose == curpose && errorpose == 0)
	{
		start->_color.a += TIME::delta;
		clickState = 0;
		if (!gameclear)
		{
			gameclear = true;
			Sound::GetIns()->PlayBg(L"res/Yeahhh.mp3");
		}
	}

	if (Director::GetIns()->MouseDown())
	{
		for (auto it : tilelist)
		{
			if (isWorldClick(it->GetRect()) && !gameclear)
			{
				if (it->state == 0) clickState = 1;
				if (it->state == 1) clickState = 2;
				if (it->state == 2) clickState = 3;
				break;
			}
		}
		if (isClick(backEditor->GetRect()))
		{
			if (really)
			{
				Director::GetIns()->ChangeScene(new SelectScene);
				return;
			}
			if (!really)
			{
				backEditor->SetTexture(L"backEditorReally.png");
				really = true;
			}
		}
		else
		{
			if (really)
			{
				backEditor->SetTexture(L"backEditor.png");
				really = false;
			}
		}
	}
	if (Director::GetIns()->MouseUp())
	{
		clickState = 0;
	}
	if (Director::GetIns()->rMouseDown())
	{
		firstpos = Director::GetIns()->GetMousePos();
	}
	if (Director::GetIns()->rMouse())
	{
		curpos = Director::GetIns()->GetMousePos();

		vec2 pos = firstpos - curpos;
		Camera::GetIns()->_camPos += pos;
		firstpos = curpos;
	}

	if (DXUTWasKeyPressed(VK_F2))
	{
		cheat = !cheat;
	}
}

void GamePlay::OnExitGamePlay()
{
	Camera::GetIns()->_camPos = { ScreenWidth / 2, ScreenHeight / 2 };
	gameclear = false;
	cheat = false;

	DeleteTile();
	DeleteFont();
	delete size;
	delete start;
	delete backEditor;
}
