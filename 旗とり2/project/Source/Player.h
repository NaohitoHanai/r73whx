#pragma once
#include "../Library/gameObject.h"

class Player : public GameObject
{
public:
	Player(); // �R���X�g���N�^�[ �ŏ���1�񂾂��Ă΂��
	~Player(); // �f�X�g���N�^�[ �Ō�ɂP�񂾂��Ă΂��
	void Update() override;
	void Draw() override;

	int hImage;
	float x, y;
	bool moved;
	int pattern;
	int counter;

	bool alive;
};
