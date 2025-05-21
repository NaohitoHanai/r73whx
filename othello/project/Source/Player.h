#pragma once
#include "../Library/GameObject.h"
#include "Board.h"

// ���[�U�[�̓��͂����āA�R�}��u��
class Player : public GameObject
{
public:
	Player(Board::CELL_STATE color);
	~Player();
	void Update() override;
	void Draw() override;
	void TurnStart(); // �����̃^�[���ɂȂ���
	bool TurnEnded(); // �����̃^�[�����I�����
private:
	Board::CELL_STATE myColor;
	bool active; // ������������
};