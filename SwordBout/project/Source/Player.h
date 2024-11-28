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

	// ステートパターンのプログラム（関数バージョン）
	enum State {
		S_STOP,
		S_ATTACK1,
		S_ATTACK2,
		S_ATTACK3,
	};
	State state; // 状態を管理する変数
	void UpdateStop();  // 状態ごとのUpdate()
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();

	void AttackEnemy();

#if 0
	float armRot;
#endif
};