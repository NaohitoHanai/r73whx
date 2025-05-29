#pragma once
#include "../Library/SceneBase.h"
#include "Player.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	int turn;
	float dispTime; // メッセージを表示する時間
	enum Phase {
		DISP_MESSAGE = 0, // ●●の番です、パスです
		PLAYING, // 入力待ち
	};
	Phase phase;
	Player* player[2];
};
