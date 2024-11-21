#pragma once
// Player.h
#include "Object3D.h"
#include "Animator.h"

class Player : public Object3D {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
private:
	Animator* anim;
	int hWeapon;

#if 0
	float armRot;
#endif
};