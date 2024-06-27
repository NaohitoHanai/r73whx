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
	void SetPosition(int x, int y);

	VECTOR GetCameraPosition() {
		return cameraPosition;
	}
private:
	bool recentJumpKey; //前のフレームのジャンプボタン

	int hImage;
	VECTOR position;
	float speedY; // ジャンプ用のYの移動速度
	bool moved;
	int pattern;
	int counter;

	bool alive;

	VECTOR cameraPosition; // カメラの位置

	bool jumping; // ジャンプ中・落下中はtrue
};
