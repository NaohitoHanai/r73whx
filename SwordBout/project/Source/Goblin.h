#pragma once
#include "Object3D.h"
#include "Animator.h"

class Goblin : public Object3D {
public:
	Goblin();
	~Goblin();
	void Update() override;
private:
	Animator* anim;
};