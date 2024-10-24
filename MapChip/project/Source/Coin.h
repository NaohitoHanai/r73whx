#pragma once
// Coin
#include "../Library/GameObject.h"

class Coin : public GameObject {
public:
	Coin();
	Coin(VECTOR pos);
	~Coin();
	void Update() override;
	void Draw() override;
private:
	VECTOR position;
	int hModel;
	bool got;
};