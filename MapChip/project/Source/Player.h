#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject {
public:
	Player();
	Player(VECTOR pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	VECTOR position;
};