#include "RedGoblinAI.h"
#include "Object3D.h"
#include "ActionBase.h"
#include "Player.h"
#include "ActRun.h"

//RedGoblinAI::RedGoblinAI()
//{
//	attackPhase = 0;
//}

RedGoblinAI::~RedGoblinAI()
{
}

void RedGoblinAI::Update()
{
	switch (attackPhase) {
	case 0: // 走り
	{
		Transform pl =
			FindGameObject<Player>()->GetTransform();
		// プレイヤーに向かわせる
		ActRun* run =
			dynamic_cast<ActRun*>(parent->actions[RedGoblin::A_RUN]);
		run->SetTarget(pl.position);
		// プレイヤーに近づいたら殴る
		// 自分の座標は、parent->transform
		// プレイヤーの座標は、	
		VECTOR diff = parent->transform.position -
			pl.position;
		if (VSize(diff) < 150)
		{
			parent->ChangeAction(RedGoblin::A_ATTACK);
			attackPhase = 1;
		}
	}
		break;
	case 1: // 殴り
		if (parent->actions[RedGoblin::A_ATTACK]
			->IsFinish())
		{
			attackPhase = 2;
		}
		break;
	case 2: // 終わり
		attackPhase = 0; // 仮で走りに戻す
		parent->ChangeAction(RedGoblin::A_RUN);
		break;
	}
}
castとは？
型を変える
float f = 10.5f;
int x = f; // Warning
int x = (int)f; // fをintにしてから代入(Cのcast)

int* p = 0x2000;
float f = (float)p;

int x = static_cast<int>(f); // 非ポインターから非ポインターへのcast
dynamic_cast // 基底クラスから派生クラスへのcast
const_cast // constを外す
reinterpret_cast // ノーチェックのcast
