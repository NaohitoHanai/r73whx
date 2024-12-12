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

	VECTOR lastP1; // 前のフレームのp1
	VECTOR lastP2; // 前のフレームのp2

	enum State {
		S_IDLE, // その場にいる
		S_RUN, // 追いかける
		S_ATTACK, // 攻撃する
		S_BACK, // 元の位置に戻る
		S_DAMAGE, // ダメージを喰らう
	};
	State state;
	void UpdateIdle();
	void UpdateRun();
	void UpdateAttack();
	void UpdateBack();
	void UpdateDamage();

	VECTOR basePosition; // 基準の位置
};