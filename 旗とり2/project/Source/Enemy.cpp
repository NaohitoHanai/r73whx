#include "Enemy.h"
#include <assert.h>
#include "Player.h"

Enemy::Enemy()
{
	hImage = LoadGraph("data/image/mob.png");
	assert(hImage > 0);

	position.x = 100;
	position.y = 200;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Player* pPlayer = FindGameObject<Player>();
	VECTOR pPos = pPlayer->GetPosition();
	// pPos�Ƀv���C���[�̍��W�Aposition�Ɏ����̍��W
	// �G���v���C���[�Ɉړ�����̂ŁA�G����v���C���[�̃x�N�g�������
	VECTOR vPlayer = pPos - position;
	VECTOR vN = VNorm(vPlayer); // ���ꂪ�����P�̃x�N�g��
	VECTOR vMove = vN * 0.8; // �v���C���[�֌���������0.05�̃x�N�g��
	position += vMove;
}

void Enemy::Draw()
{
	DrawRectGraph(position.x, position.y, 0, 0, 64, 64, hImage, TRUE);
}

VECTOR Enemy::GetPosition()
{
	return position;
}
