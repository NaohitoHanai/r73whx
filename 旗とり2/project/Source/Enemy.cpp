#include "Enemy.h"
#include <assert.h>

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
	DrawRectGraph(position.x, position.y, 0, 0, 64, 64, hImage, TRUE);
}
