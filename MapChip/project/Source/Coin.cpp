#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
}

Coin::Coin(VECTOR pos)
{
	position = pos;
	hModel = MV1LoadModel("data/coin.mv1");
	got = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* pl = FindGameObject<Player>();
	if (pl == nullptr) {
		return;
	}
	if (got) {
		// �v���C���[�ɋz������
		// �@�����iCoin�j����v���C���[�ւ̃x�N�g�������
		VECTOR v = pl->Position() - position;
		// �A�A�@�̃x�N�g���̒������A�z�����݂̑��x(5.0f)�ɂ���
		VECTOR v2 = VNorm(v) * gotSpeed;
		// �B�A�A�������̍��W�ɉ�����
		position = position + v2;
		// �C�������A�v���C���[�ɋ߂Â�����(40.0f�ȓ�)�ADestroyMe()����
		if (VSize(v) - gotSpeed < 40.0f) {
			DestroyMe();
		}
		gotSpeed += 0.5f;
		return;
	}

	VECTOR plPos = pl->Position(); // �v���C���[�̍��W
	// �����̍��W��position
	VECTOR diff = plPos - position;
	float len = VSize(diff);
	if (len < 200.0f) {
		got = true;
		gotSpeed = 3.0f;
	}
}

void Coin::Draw()
{
	MV1SetRotationXYZ(hModel, VGet(0, DX_PI / 2, 0));
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
