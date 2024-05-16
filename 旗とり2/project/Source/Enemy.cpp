#include "Enemy.h"
#include <assert.h>

Enemy::Enemy()
{
	hImage = LoadGraph("data/image/mob.png");
	assert(hImage > 0);

	x = 100;
	y = 200;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
}
