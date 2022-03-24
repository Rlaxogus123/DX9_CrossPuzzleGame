#include "DXUT.h"
#include "Include.h"

bool SelectScene::isClick(RECT r)
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

void SelectScene::Init()
{
	playPuzzle = new Sprite(L"PlayPuzzle.png");
	playPuzzle->_position = { ScreenWidth/2, 400 };

	createPuzzle = new Sprite(L"createPuzzle.png");
	createPuzzle->_position = { ScreenWidth / 2, 700 };

	backTitle = new Sprite(L"backTitle.png");
	backTitle->_position = { 100, 970 };
	backTitle->_isUI = true;
}

void SelectScene::Update()
{
	ifstream open("res/tileData.txt");
	if (open.is_open())
		playPuzzle->SetTexture(L"PlayPuzzle.png");
	else
		playPuzzle->SetTexture(L"PlayPuzzleError.png");

	if (Director::GetIns()->MouseDown())
	{
		if (isClick(playPuzzle->GetRect()) && playPuzzle->_texture->_path == L"PlayPuzzle.png")
		{
			Director::GetIns()->ChangeScene(new GamePlayScene);
			return;
		}

		if (isClick(createPuzzle->GetRect()))
		{
			Director::GetIns()->ChangeScene(new GameScene);
			return;
		}

		if (isClick(backTitle->GetRect()))
		{
			Director::GetIns()->ChangeScene(new TitleScene);
			return;
		}
	}
}

void SelectScene::OnExit()
{
	delete playPuzzle;
	delete backTitle;
	delete createPuzzle;
}
