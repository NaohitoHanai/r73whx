#include "PlayScene.h"
#include "Board.h"
#include "Player.h"
#include "ComPlayer.h"

PlayScene::PlayScene()
{
	new Board();
	if (CheckHitKey(KEY_INPUT_B)) {
		player[0] = new ComPlayer(Board::BLACK);
		player[1] = new Player(Board::WHITE);
	} else {
		player[0] = new Player(Board::BLACK);
		player[1] = new ComPlayer(Board::WHITE);
	}
	turn = 0;
	phase = Phase::DISP_MESSAGE;
	dispTime = 0.5f; // ï\é¶éûä‘
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (phase == Phase::DISP_MESSAGE) {
		dispTime -= Time::DeltaTime();
		if (dispTime <= 0) {
			Board* b = FindGameObject<Board>();
			if (b->IsPass(turn==0 ? Board::BLACK : Board::WHITE))
			{
				// ÉpÉXÇÃéûÇ…Ç‚ÇÈÇ±Ç∆
				if (turn == 0)
					turn = 1;
				else
					turn = 0;
				phase = Phase::DISP_MESSAGE;
				dispTime = 0.5f;
			} else {
				player[turn]->TurnStart();
				phase = Phase::PLAYING;
			}
		}
	} else if (phase == Phase::PLAYING){
		if (player[turn]->TurnEnded()) {
			if (turn == 0)
				turn = 1;
			else
				turn = 0;
			phase = Phase::DISP_MESSAGE;
			dispTime = 0.5f;
		}
	}
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	if (dispTime > 0) {
		int size = GetFontSize();
		SetFontSize(60);
		if (turn == 0) {
			DrawString(300, 200, "çïÇÃî‘Ç≈Ç∑", GetColor(255, 0, 0));
		} else {
			DrawString(300, 200, "îíÇÃî‘Ç≈Ç∑", GetColor(255, 0, 0));
		}
		SetFontSize(size);
	}
}
