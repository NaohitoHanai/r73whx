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
}

void Enemy::Draw()
{
	Player* pPlayer = FindGameObject<Player>();
	VECTOR p = position - pPlayer->GetCameraPosition();
	DrawRectGraph(p.x, p.y, 0, 0, 64, 64, hImage, TRUE);
}

void Enemy::SetPosition(int x, int y)
{
	position = VGet(x, y, 0);
}