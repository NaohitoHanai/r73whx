#include "Enemy.h"
#include <assert.h>
#include "Player.h"
#include "config.h"
#include "../Library/time.h"

Enemy::Enemy()
{
	hImage = LoadGraph("data/image/mob.png");
	assert(hImage > 0);

	position.x = 100;
	position.y = 200;
	r = 0;
	state = sFLY;
	timer = 1.0f;
}

Enemy::~Enemy()
{
	DeleteGraph(hImage);
}

void Enemy::Update()
{
	Player* pPlayer = FindGameObject<Player>();
	VECTOR p = position - pPlayer->GetCameraPosition();
	if (p.x < -64 || p.x > SCREEN_WIDTH) {
		return;
	}
	
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
	velocity.x = -1;
	velocity.y = sin(r);
	position += velocity;
	r += 0.05f;

	timer -= Time::DeltaTime();
	if (timer <= 0.0f) {
		state = sATTACK;
	}
}

void Enemy::updateAttack()
{
	// 2D��90�x��]������ɂ�(-y, x)
	VECTOR right = VGet(-velocity.y, velocity.x, 0);
	Player* pPlayer = FindGameObject<Player>();
	VECTOR diff = pPlayer->GetPosition() - position;
	float ip/*����*/ = VDot(right, diff);
	if (ip > 0) {
		// �E��]
		velocity = velocity * MGetRotZ(DegToRad(1.0));
	}
	else if (ip < 0) {
		// ����]
		velocity = velocity * MGetRotZ(DegToRad(-1.0));
	}
	velocity = VNorm(velocity) * 2.0f;
	position += velocity;

	if (VSize(diff)<120.0f) {
		state = sFLY;
		timer = GetRand(10);// GetRand(n)��0�`n�̗���
	}
}

void Enemy::updateAway()
{
}

void Enemy::updateDead()
{
}
