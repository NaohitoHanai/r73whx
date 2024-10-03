#pragma once
#include "../Library/gameObject.h"

class Stone : public GameObject
{
public:
	Stone(); // コンストラクター 最初に1回だけ呼ばれる
	~Stone(); // デストラクター 最後に１回だけ呼ばれる
	void Update() override;
	void Draw() override;

	void SetPosition(VECTOR pos);
private:
	int hImage;
	VECTOR position;
	VECTOR velocity;
};
