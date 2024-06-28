#pragma once
#include "../Library/gameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(); // �R���X�g���N�^�[ �ŏ���1�񂾂��Ă΂��
	~Enemy(); // �f�X�g���N�^�[ �Ō�ɂP�񂾂��Ă΂��
	void Update() override;
	void Draw() override;
	VECTOR GetPosition() {
		return position;
	}
	void SetPosition(int x, int y);
private:
	int hImage;
	VECTOR position;
	float r;

	// ��ԑJ��
	enum State {
		sFLY = 0,
		sATTACK,
		sAWAY,
		sDEAD,
	};
	State state;
	void updateFly();
	void updateAttack();
	void updateAway();
	void updateDead();
};