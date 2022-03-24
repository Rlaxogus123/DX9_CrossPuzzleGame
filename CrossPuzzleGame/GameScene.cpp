#include "DXUT.h"
#include "Include.h"

void GameScene::Init()
{
	cout << "°ÔÀÓ¾À" << endl;
	Game::GetIns()->GameInit();
}

void GameScene::Update()
{
	Game::GetIns()->GameUpdate();
}

void GameScene::OnExit()
{
	Game::GetIns()->GameExit();
}
