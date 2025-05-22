#pragma once
#include "../Library/GameObject.h"
#include "Board.h"

// ���[�U�[�̓��͂����āA�R�}��u��
class Player : public GameObject
{
public:
	Player(Board::CELL_STATE color);
	virtual ~Player();
	virtual void Update() override;
	virtual void Draw() override;
	void TurnStart(); // �����̃^�[���ɂȂ���
	bool TurnEnded(); // �����̃^�[�����I�����
protected: // �h���N���X�ł��g����悤�ɂ���
	Board::CELL_STATE myColor;
	bool active; // ������������
};