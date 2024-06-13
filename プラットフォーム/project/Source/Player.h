#pragma once
#include "../Library/gameObject.h"

class Player : public GameObject
{
public:
	Player(); // コンストラクター 最初に1回だけ呼ばれる
	~Player(); // デストラクター 最後に１回だけ呼ばれる
	void Update() override;
	void Draw() override;
	VECTOR GetPosition() {
		return position;
	}
	VECTOR GetCameraPosition() {
		return cameraPosition;
	}
private:
	int hImage;
	VECTOR position;
	bool moved;
	int pattern;
	int counter;

	bool alive;

	VECTOR cameraPosition; // カメラの位置
};
