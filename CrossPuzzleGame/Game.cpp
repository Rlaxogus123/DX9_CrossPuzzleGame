#include "DXUT.h"
#include "Include.h"

void Game::CreateTile()
{
	exporttile->_position = { 400,80 };

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			tile = new Tile;
			tile->_layer = -1;
			tile->_visible = true;
			tile->_position = {(float)(200 + x * 32),(float)(200 + y * 32) };
			tile->x = x;
			tile->y = y;

			tilelist.push_back(tile);
		}
	}
}

void Game::DeleteTile()
{
	for (auto it : tilelist)
	{
		it->_sprite->Release();
		delete it;
	}
	tilelist.clear();
}

void Game::DeleteFont()
{
	for (auto it : fontlist)
	{
		it->_font->Release();
		delete it;
	}
	fontlist.clear();
}

void Game::verticalReadLine()
{
	for (int j = 0; j < sizeY; j++)
	{
		int count = 0;
		vector<int> countlist;

		Tile* curTile = nullptr;

		for (int i = 0; i < sizeX; i++)
		{
			curTile = Game::GetIns()->tilelist[i + (j*sizeX)];
			if (curTile->state == 1)
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
			countFont->_position = { (float)(160),190 + ((float)j*32) };
			countFont->CreateMyfont(1.2, 700);
			countFont->SetString("0");

			fontlist.push_back(countFont);
		}
		for (int i = 0; i < countlist.size(); i++)
		{
			Font* countFont = new Font;
			countFont->_position = { (float)(160 - (32 * i)),190 + ((float)j*32) };
			countFont->CreateMyfont(1.2, 700);
			char buff[5];
			sprintf(buff, "%d", countlist[countlist.size() - i - 1]);
			countFont->SetString(buff);
			fontlist.push_back(countFont);
		}
	}
}

void Game::horizontalReadLine()
{
	for (int x = 0; x < sizeX; x++)
	{
		int count = 0;
		vector<int> countlist;

		Tile* curTile = nullptr;

		for (int y = 0; y < sizeY; y++)
		{
			curTile = Game::GetIns()->tilelist[x + (y * sizeX)];
			if (curTile->state == 1)
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
			countFont->_position = { (float)(200 + ((float)x*32)), 158 };
			countFont->CreateMyfont(1.2, 700);
			countFont->SetString("0");

			fontlist.push_back(countFont);
		}
		for (int i = 0; i < countlist.size(); i++)
		{
			Font* countFont = new Font;
			countFont->_position = { (float)(198 + ((float)x * 32)), 158 - ((float)i*32) };
			countFont->CreateMyfont(1.2, 700);
			char buff[5];
			sprintf(buff, "%d", countlist[countlist.size() - i - 1]);
			countFont->SetString(buff);
			fontlist.push_back(countFont);
		}
	}
}

void Game::SafeTileData()
{
	ofstream out("res/tileData.txt");

	if (out.is_open())
	{
		out << sizeX << endl;
		out << sizeY << endl;
		for (int i = 0; i < tilelist.size(); i++)
		{
			out << tilelist[i]->state << endl;
		}
	}

	out.close();
}

bool Game::isClick(RECT r)
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

bool Game::isWorldClick(RECT r)
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

void Game::GameInit()
{
	sizeX = 10;
	sizeY = 10;

	clickState = 0;

	uptileX = new Sprite(L"head.png");
	uptileX->_rotation = D3DXToRadian(270);
	uptileX->_position = { 120,16 * 2 };
	uptileX->_isUI = true;
	downtileX = new Sprite(L"head.png");
	downtileX->_rotation = D3DXToRadian(90);
	downtileX->_position = { 120,16 * 8 };
	downtileX->_isUI = true;

	uptileY = new Sprite(L"head.png");
	uptileY->_rotation = D3DXToRadian(270);
	uptileY->_position = { 170,16 * 2 };
	uptileY->_isUI = true;

	downtileY = new Sprite(L"head.png");
	downtileY->_rotation = D3DXToRadian(90);
	downtileY->_position = { 170,16 * 8 };
	downtileY->_isUI = true;

	createtile = new Sprite(L"createTile.png");
	createtile->_position = { 250,80 };
	createtile->_isUI = true;

	exporttile = new Sprite(L"exportTile.png");
	exporttile->_position = { 400,-999 };
	exporttile->_isUI = true;

	exportSuccess = new Sprite(L"exportSuccess.png");
	exportSuccess->_position = { 550, 80 };
	exportSuccess->_color.a = 0;
	exportSuccess->_isUI = true;

	backEditor = new Sprite(L"backEditor.png");
	backEditor->_position = { 100,970 };
	backEditor->_isUI = true;
	really = false;

	size = new Font;
	size->_isUI = true;
	size->_color = color(1, 1, 0, 1);
	size->_position = { 0,60 };
	size->CreateMyfont(2, 900);
}

void Game::GameUpdate()
{
	char buff[100];
	sprintf(buff, "Size : %dx%d", sizeX, sizeY);
	size->SetString(buff);
	exportSuccess->_color.a -= TIME::delta;

	if (tilelist.size() == sizeX * sizeY)
	{
		exporttile->_visible = true;
		createtile->_visible = false;
	}
	else
	{
		exporttile->_visible = false;
		createtile->_visible = true;
	}

	

	if (Director::GetIns()->MouseDown())
	{
		if (isClick(createtile->GetRect()) && createtile->_visible)
		{
			DeleteFont();
			DeleteTile();
			CreateTile();
		}
		if (isClick(exporttile->GetRect()) && exporttile->_visible)
		{
			DeleteFont();
			SafeTileData();
			verticalReadLine();
			horizontalReadLine();
			exportSuccess->_color.a = 2;
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

		if (isClick(uptileX->GetRect()))
			if (sizeX < 30) sizeX += 5;
		if (isClick(downtileX->GetRect()))
			if (sizeX > 5) sizeX -= 5;
		if (isClick(uptileY->GetRect()))
			if (sizeY < 30) sizeY += 5;
		if (isClick(downtileY->GetRect()))
			if (sizeY > 5) sizeY -= 5;

		for (auto it : tilelist)
		{
			if (isWorldClick(it->GetRect()))
			{
				if (it->state == 0) clickState = 1;
				if (it->state == 1) clickState = 2;
				cout << "클릭댐" << endl;
				break;
			}
		}
	}

	if (Director::GetIns()->MouseUp())
	{
		cout << "클릭 풀림" << endl;
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
}

void Game::GameExit()
{
	Camera::GetIns()->_camPos = { ScreenWidth / 2, ScreenHeight / 2 };
	DeleteTile();
	DeleteFont();

	delete size;
	
	delete createtile;
	delete exporttile;
	delete exportSuccess;
	delete backEditor;

	delete uptileX;
	delete uptileY;
	delete downtileX;
	delete downtileY;
}