#pragma once
#include "../Library/gameObject.h"

class Item : public GameObject
{
public:
	Item(); // �R���X�g���N�^�[ �ŏ���1�񂾂��Ă΂��
	~Item(); // �f�X�g���N�^�[ �Ō�ɂP�񂾂��Ă΂��
	void Update() override;
	void Draw() override;
	VECTOR GetPosition();
private:
	int hImage;
	VECTOR position;
};