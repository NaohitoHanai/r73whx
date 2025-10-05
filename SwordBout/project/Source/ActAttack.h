#pragma once
//ActAttack.h
#include "ActionBase.h"

class ActAttack : public ActionBase
{
public:
	ActAttack(Object3D* base);
	~ActAttack();
	void Update() override;
	void Suspend() override;
	void Resume() override;
};