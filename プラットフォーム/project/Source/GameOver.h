#pragma once
// GameOver.h
#include "../Library/gameObject.h"

class GameOver : public GameObject {
public:
	GameOver();
	~GameOver();
	void Update();
	void Draw();
private:
	VECTOR position;
	int hImage;

	float startY;
	float goalY;
	int frame;
};