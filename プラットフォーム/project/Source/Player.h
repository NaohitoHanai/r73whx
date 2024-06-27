#pragma once
#include "../Library/gameObject.h"

class Player : public GameObject
{
public:
	Player(); // �R���X�g���N�^�[ �ŏ���1�񂾂��Ă΂��
	~Player(); // �f�X�g���N�^�[ �Ō�ɂP�񂾂��Ă΂��
	void Update() override;
	void Draw() override;
	VECTOR GetPosition() {
		return position;
	}
	void SetPosition(int x, int y);

	VECTOR GetCameraPosition() {
		return cameraPosition;
	}
private:
	bool recentJumpKey; //�O�̃t���[���̃W�����v�{�^��

	int hImage;
	VECTOR position;
	float speedY; // �W�����v�p��Y�̈ړ����x
	bool moved;
	int pattern;
	int counter;

	bool alive;

	VECTOR cameraPosition; // �J�����̈ʒu

	bool jumping; // �W�����v���E��������true
};
