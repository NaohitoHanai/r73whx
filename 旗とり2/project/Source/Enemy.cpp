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
	// pPosにプレイヤーの座標、positionに自分の座標
	// 敵がプレイヤーに移動するので、敵からプレイヤーのベクトルを作る
	VECTOR vPlayer = pPos - position;
	VECTOR vN = VNorm(vPlayer); // これが長さ１のベクトル
	VECTOR vMove = vN * 0.8; // プレイヤーへ向かう長さ0.05のベクトル
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
