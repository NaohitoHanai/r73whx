#pragma once
#include "Object3D.h"
#include "Animator.h"
#include "ActionBase.h"
class RedGoblinAI;

class RedGoblin : public Object3D {
public:
	RedGoblin();
	RedGoblin(VECTOR pos, float rotY);
	~RedGoblin();
	void Update() override;
	void Draw() override;
	void SetPosition(VECTOR pos) {
		transform.position = pos;
	}

	bool CheckLine(VECTOR p1, VECTOR p2);

	friend class ActRun;
	friend class ActAttack;
	friend class RedGoblinAI;
private:
	Animator* anim;
	int hWeapon;
	enum ActID {
		A_ATTACK = 0,
		A_RUN,
		A_MAX
	};
	ActionBase* actions[ActID::A_MAX];
	ActID actID;
	RedGoblinAI* ai;
	void ChangeAction(ActID act);
};