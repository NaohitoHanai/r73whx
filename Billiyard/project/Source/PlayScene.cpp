#include "PlayScene.h"
#include "Ball.h"
#include "BallManager.h"
PlayScene::PlayScene()
{
	for (int i = 0; i < 16; i++) {
		new Ball(i, VGet((i%8) * 100+200, (i/8)*100+100, 0));
	}
	new BallManager();
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
