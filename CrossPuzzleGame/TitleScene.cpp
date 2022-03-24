#include "DXUT.h"
#include "Include.h"

bool TitleScene::isClick(RECT r)
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

void TitleScene::Init()
{
	background = new Sprite(L"background.jpg");
	background->_position = { ScreenWidth / 2, ScreenHeight / 2 };
	background->_isUI = true;
	background->_layer = -9999;
	background->_scale = { 1,1 };

	title = new Sprite(L"nonoGram.png");
	title->_pivot = { 0,0 };
	title->_color.a = 0;

	start = new Sprite(L"Start.png");
	start->_scale = { 0.7,0.7 };
	start->_position = { 300,700 };

	end = new Sprite(L"End.png");
	end->_scale = { 0.7,0.7 };
	end->_position = { 300,850 };
}

void TitleScene::Update()
{
	title->_color.a += TIME::delta / 2;

	if (Director::GetIns()->MouseDown())
	{
		if (isClick(start->GetRect()))
		{
			Director::GetIns()->ChangeScene(new SelectScene);
			return;
		}
		if (isClick(end->GetRect()))
		{
			exit(0);
			return;
		}
	}
}

void TitleScene::OnExit()
{
	delete title;
	delete start;
	delete end;
}
