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
	case 0: // ����
	{
		Transform pl =
			FindGameObject<Player>()->GetTransform();
		// �v���C���[�Ɍ����킹��
		ActRun* run =
			dynamic_cast<ActRun*>(parent->actions[RedGoblin::A_RUN]);
		run->SetTarget(pl.position);
		// �v���C���[�ɋ߂Â����牣��
		// �����̍��W�́Aparent->transform
		// �v���C���[�̍��W�́A	
		VECTOR diff = parent->transform.position -
			pl.position;
		if (VSize(diff) < 150)
		{
			parent->ChangeAction(RedGoblin::A_ATTACK);
			attackPhase = 1;
		}
	}
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
cast�Ƃ́H
�^��ς���
float f = 10.5f;
int x = f; // Warning
int x = (int)f; // f��int�ɂ��Ă�����(C��cast)

int* p = 0x2000;
float f = (float)p;

int x = static_cast<int>(f); // ��|�C���^�[�����|�C���^�[�ւ�cast
dynamic_cast // ���N���X����h���N���X�ւ�cast
const_cast // const���O��
reinterpret_cast // �m�[�`�F�b�N��cast
