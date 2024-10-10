#include "PlayScene.h"
#include <DxLib.h>
#include "Field.h"

PlayScene::PlayScene()
{
	SetCameraPositionAndTarget_UpVecY(
		VGet(200.0f, 1000.0f, -1000.0f),
		VGet(0, 0, 0));

	new Field();
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
	DrawLine3D(VGet(0, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, 0, 0), VGet(0, 100, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, 0), VGet(0, 0, 100), GetColor(0, 0, 255));

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
