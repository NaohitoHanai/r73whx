#pragma once
#include "../Library/GameObject.h"

// ���[�U�[�̓��͂����āA�R�}��u��
class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
};