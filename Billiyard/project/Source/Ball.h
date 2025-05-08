#pragma once
#include "../Library/GameObject.h"

class Ball : public GameObject
{
public:
	Ball(int num, VECTOR pos);
	~Ball();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	VECTOR position;
	VECTOR velocity;
	int number; // ©•ª‚Ì”Ô†

	void Control(); // 0”Ô‚Ì‹Ê‚ğ‘€ì‚Å‚«‚é
	float angle; // ”­ËŠp
	float power; // ”­Ë‚Ì—Í
};