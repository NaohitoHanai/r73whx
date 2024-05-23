#pragma once
#include "../Library/gameObject.h"

class Item : public GameObject
{
public:
	Item(); // コンストラクター 最初に1回だけ呼ばれる
	~Item(); // デストラクター 最後に１回だけ呼ばれる
	void Update() override;
	void Draw() override;
	VECTOR GetPosition();
private:
	int hImage;
	VECTOR position;
};