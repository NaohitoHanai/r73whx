#pragma once
#include "../Library/gameObject.h"

class Stone : public GameObject
{
public:
	Stone(); // �R���X�g���N�^�[ �ŏ���1�񂾂��Ă΂��
	~Stone(); // �f�X�g���N�^�[ �Ō�ɂP�񂾂��Ă΂��
	void Update() override;
	void Draw() override;

	void SetPosition(VECTOR pos);
private:
	int hImage;
	VECTOR position;
	VECTOR velocity;
};
