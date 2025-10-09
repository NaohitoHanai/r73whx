#include "RedGoblinAI.h"
#include "Object3D.h"
#include "ActionBase.h"
#include "Player.h"

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
		// プレイヤーに近づいたら殴る
		// 自分の座標は、parent->transform
		// プレイヤーの座標は、	
		Transform pl = 
			FindGameObject<Player>()->GetTransform();
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
