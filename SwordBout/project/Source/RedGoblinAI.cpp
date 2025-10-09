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
	case 0: // ����
		// �v���C���[�ɋ߂Â����牣��
		// �����̍��W�́Aparent->transform
		// �v���C���[�̍��W�́A	
		Transform pl = 
			FindGameObject<Player>()->GetTransform();
		break;
	case 1: // ����
		if (parent->actions[RedGoblin::A_ATTACK]
			->IsFinish())
		{
			attackPhase = 2;
		}
		break;
	case 2: // �I���
		attackPhase = 0; // ���ő���ɖ߂�
		parent->ChangeAction(RedGoblin::A_RUN);
		break;
	}
}
