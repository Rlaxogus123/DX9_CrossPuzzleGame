#include "DXUT.h"
#include "Include.h"

void GamePlayScene::Init()
{
	GamePlay::GetIns()->InitGamePlay();
}

void GamePlayScene::Update()
{
	GamePlay::GetIns()->UpdateGamePlay();
}

void GamePlayScene::OnExit()
{
	GamePlay::GetIns()->OnExitGamePlay();
}
