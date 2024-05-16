#include "Player.h"
#include <assert.h>
#include "config.h"
#include "Enemy.h"

Player::Player()
{
	hImage = LoadGraph("data/image/aoi.png");
	assert(hImage>0);
	position.x = 10;
	position.y = 20;
	pattern = 0;
	counter = 0;
	alive = true;
}

Player::~Player()
{
}


void Player::Update()
{
	Enemy* pEnemy = FindGameObject<Enemy>();
	VECTOR enePos = pEnemy->GetPosition();
	VECTOR diff = enePos - position;
	if (VSize(diff) < 32+32) {
		alive = false;
	}
	if (alive) {
		moved = false;
		if (CheckHitKey(KEY_INPUT_D)) {
			position.x += 1;
			moved = true;
			if (position.x >= SCREEN_WIDTH - 64) {
				position.x = SCREEN_WIDTH - 64;
			}
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			position.x -= 1;
			moved = true;
			if (position.x <= 0)
				position.x = 0;
		}
		if (CheckHitKey(KEY_INPUT_W)) {
			position.y -= 1;
			moved = true;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			moved = true;
			position.y += 1;
		}
		if (moved) {
			// アニメーションの処理
			if (++counter == 10) {
				counter = 0;
#if 0
				++pattern;
				pattern %= 4;
#else
				pattern = (pattern + 1) % 4;
#endif
			}
		}
		else {
			pattern = 0;
			counter = 0;
		}
	}
	else {
		// 泣いてる時
	}
}

void Player::Draw()
{
//	DrawGraph(x, y, hImage, TRUE);
	if (alive) {
		DrawRectGraph(position.x, position.y, pattern * 64, 0, 64, 64, hImage, TRUE);
	}
	else {
		DrawRectGraph(position.x, position.y, 0, 4*64, 64, 64, hImage, TRUE);
	}
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Xは%f", position.x);
}

VECTOR Player::GetPosition()
{
	return position;
}
