#pragma once
#include "../Library/gameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(); // コンストラクター 最初に1回だけ呼ばれる
	~Enemy(); // デストラクター 最後に１回だけ呼ばれる
	void Update() override;
	void Draw() override;
	VECTOR GetPosition() {
		return position;
	}
private:
	int hImage;
	VECTOR position;
};