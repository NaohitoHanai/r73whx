#pragma once
//Score.h
#include "../Library/gameObject.h"

class Score : public GameObject {
public:
	Score();
	~Score();
	void Update() override;
	void Draw() override;
	void Add(int val);
private:
	int score;
	int highScore;
};