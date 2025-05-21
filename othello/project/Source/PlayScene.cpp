#include "PlayScene.h"
#include "Board.h"
#include "Player.h"

PlayScene::PlayScene()
{
	new Board();
	player[0] = new Player(Board::BLACK);
	player[1] = new Player(Board::WHITE);
	turn = 0;
	player[turn]->TurnStart();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (player[turn]->TurnEnded()) {
		if (turn==0)
			turn = 1;
		else
			turn = 0;
		player[turn]->TurnStart();
	}
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
