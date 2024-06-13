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
	VECTOR GetCameraPosition() {
		return cameraPosition;
	}
private:
	int hImage;
	VECTOR position;
	bool moved;
	int pattern;
	int counter;

	bool alive;

	VECTOR cameraPosition; // �J�����̈ʒu
};
