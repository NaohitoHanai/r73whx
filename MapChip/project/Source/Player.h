#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject {
public:
	Player();
	Player(VECTOR pos);
	~Player();
	void Update() override;
	void Draw() override;
	VECTOR Position() { return position; }
private:
	VECTOR position;

	VECTOR start; // ��Ԃ̃X�^�[�g�n�_
	VECTOR goal;  // ��Ԃ̃S�[���n�_
	int frameCounter; // �o�ߎ��ԁi�t���[�����j
	int totalFrame;  // �S�̎���

	void MoveTo(VECTOR move);
};