#include "ResultScene.h"
#include <DxLib.h>

ResultScene::ResultScene()
{
	frame = 0;
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	frame += 1;
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void ResultScene::Draw()
{
	int size = GetFontSize();
	SetFontSize(40);
	DrawString(300, 100, "RESULT", GetColor(255, 0, 0));
	DrawFormatString(200, 300, GetColor(255, 255, 255), "HIGH SCORE %6d",
		100);// 本当はハイスコア表示
	DrawString(300, 500, "PUSH SPACE KEY", GetColor(255, 0, 0));
	SetFontSize(size);
}
