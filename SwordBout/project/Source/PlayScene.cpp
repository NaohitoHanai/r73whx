#include "PlayScene.h"
#include <DxLib.h>
#include "Player.h"
#include "Field.h"
#include "Goblin.h"

int n = 0;

PlayScene::PlayScene()
{
	SetCameraPositionAndTarget_UpVecY(
		VGet(0, 300.0f, -500.0f),
		VGet(0, 100.0f, 0));
	new Player();
	new Field();
	new Goblin(VGet(100,0,0), 0);
	new Goblin(VGet(0,0,100), DegToRad(90.0));
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
