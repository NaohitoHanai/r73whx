#include "Enemy.h"
#include <assert.h>
#include "Player.h"

Enemy::Enemy()
{
	hImage = LoadGraph("data/image/mob.png");
	assert(hImage > 0);

	position.x = 100;
	position.y = 200;
	r = 0;
	state = sFLY;
}

Enemy::~Enemy()
{
	DeleteGraph(hImage);
}

void Enemy::Update()
{
	if (state == sFLY) {
		updateFly();
	}
	else if (state == sATTACK) {
		updateAttack();
	}
	else if (state == sAWAY) {
		updateAway();
	}
	else if (state == sDEAD) {
		updateDead();
	}
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

void Enemy::updateFly()
{
	position.x -= 1;
	r += 0.05f;
	position.y += sin(r);
}

void Enemy::updateAttack()
{
}

void Enemy::updateAway()
{
}

void Enemy::updateDead()
{
}
