#include "DXUT.h"
#include "Include.h"

void GameScene::Init()
{
	cout << "���Ӿ�" << endl;
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
