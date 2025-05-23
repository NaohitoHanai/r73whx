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
	int number; // 自分の番号

	void Control(); // 0番の玉を操作できる
	float angle; // 発射角
	float power; // 発射の力
};