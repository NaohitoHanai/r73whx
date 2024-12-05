#pragma once
#include "Object3D.h"
#include "Animator.h"

class Goblin : public Object3D {
public:
	Goblin();
	Goblin(VECTOR pos, float rotY);
	~Goblin();
	void Update() override;
	void Draw() override;
	void SetPosition(VECTOR pos) {
		transform.position = pos;
	}

	bool CheckLine(VECTOR p1, VECTOR p2);
private:
	Animator* anim;

	int hWeapon;
//	bool damaged;

	VECTOR lastP1; // �O�̃t���[����p1
	VECTOR lastP2; // �O�̃t���[����p2

	enum State {
		S_IDLE,
		S_RUN,
		S_ATTACK,
		S_DAMAGE,
	};
	State state;
	void UpdateIdle();
	void UpdateRun();
	void UpdateAttack();
	void UpdateDamage();
};