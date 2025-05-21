#pragma once
#include "../Library/GameObject.h"
#include "Board.h"

// ユーザーの入力を見て、コマを置く
class Player : public GameObject
{
public:
	Player(Board::CELL_STATE color);
	~Player();
	void Update() override;
	void Draw() override;
	void TurnStart(); // 自分のターンになった
	bool TurnEnded(); // 自分のターンが終わった
private:
	Board::CELL_STATE myColor;
	bool active; // 自分が活動中
};