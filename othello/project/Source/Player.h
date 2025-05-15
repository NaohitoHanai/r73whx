#pragma once
#include "../Library/GameObject.h"

// ユーザーの入力を見て、コマを置く
class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
};