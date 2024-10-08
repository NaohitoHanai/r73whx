#include "playScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Score.h"
#include "PlayTime.h"
#include "Map.h"
#include "Square.h"

PlayScene::PlayScene()
{
	Instantiate<Square>();
	Instantiate<Map>();
	Instantiate<Player>();
//	Instantiate<Enemy>();
//	Instantiate<Item>();
//	Instantiate<Item>();
	Instantiate<Score>();
	Instantiate<PlayTime>();
}

PlayScene::~PlayScene()
{
}

float x = 0;
float dx = 5;
bool right = true;

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
	if (CheckHitKey(KEY_INPUT_R)) {
		SceneManager::ChangeScene("ResultScene");
	}
	SceneBase::Update();

	// 速度を持たせる方法
	//if (x > 400) {
	//	dx = -5;
	//}
	//if (x <= 0) {
	//	dx = 5;
	//}
	//x += dx;

	// 向きを持たせる方法
	if (right == true) {
		x += 5;
	}
	else {
		x -= 5;
	}
	if (x >= 400) {
		right = false;
	}
	if (x <= 0) {
		right = true;
	}
}

void PlayScene::Draw()
{
	SceneBase::Draw();

	DrawString(x, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
