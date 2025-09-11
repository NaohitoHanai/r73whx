#include "PlayScene.h"
#include "Boid.h"
#include "BoidManager.h"
#include "Screen.h"

PlayScene::PlayScene()
{
	new BoidManager();
	for (int i = 0; i < 500; i++) {
		int x = rand() % Screen::WIDTH;
		int y = rand() % Screen::HEIGHT;
		new Boid(x, y);
	}
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
