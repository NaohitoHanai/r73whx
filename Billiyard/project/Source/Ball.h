#pragma once
#include "../Library/GameObject.h"

class Ball : public GameObject
{
public:
	Ball(int num, VECTOR pos);
	~Ball();
	void Update() override;
	void Draw() override;
	void ResetVec();
	void HitBall(Ball* b);
	void AddVec();
private:
	int hImage;
	VECTOR position;
	VECTOR velocity;
	VECTOR addVec;
	int number; // �����̔ԍ�

	void Control(); // 0�Ԃ̋ʂ𑀍�ł���
	float angle; // ���ˊp
	float power; // ���˂̗�
};