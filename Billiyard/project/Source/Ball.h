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
	int number; // ©•ª‚Ì”Ô†

	void Control(); // 0”Ô‚Ì‹Ê‚ğ‘€ì‚Å‚«‚é
	float angle; // ”­ËŠp
	float power; // ”­Ë‚Ì—Í
};