#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject {
public:
	Player();
	Player(VECTOR pos);
	~Player();
	void Update() override;
	void Draw() override;
	VECTOR Position() { return position; }
private:
	VECTOR position;

	VECTOR start; // 補間のスタート地点
	VECTOR goal;  // 補間のゴール地点
	int frameCounter; // 経過時間（フレーム数）
	int totalFrame;  // 全体時間

	void MoveTo(VECTOR move);
};