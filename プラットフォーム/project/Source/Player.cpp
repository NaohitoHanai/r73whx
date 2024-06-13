#include "Player.h"
#include <assert.h>
#include "config.h"
#include "Enemy.h"

Player::Player()
{
	hImage = LoadGraph("data/image/aoi.png");
	assert(hImage>0);
	position.x = 0;
	position.y = 20;
	pattern = 0;
	counter = 0;
	alive = true;

	cameraPosition.x = 0;
	cameraPosition.y = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	Enemy* pEnemy = FindGameObject<Enemy>();
	VECTOR ePos = pEnemy->GetPosition();
	VECTOR d = ePos - position;
	if (VSize(d) < 32+32){
		alive = false;
	}

	if (alive) {
		moved = false;
		if (CheckHitKey(KEY_INPUT_D)) {
			position.x += 5;
			moved = true;
//			if (position.x >= SCREEN_WIDTH - 64) {
//				position.x = SCREEN_WIDTH - 64;
//			}
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			position.x -= 5;
			moved = true;
			if (position.x-cameraPosition.x <= 0)
				position.x = cameraPosition.x;
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
	VECTOR p = position - cameraPosition;
	if (p.x > 200) {
		// 200 = position.x - cameraPosition.xだから
		cameraPosition.x = position.x - 200;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
		cameraPosition.y = 5;
	else
		cameraPosition.y = 0;

}

void Player::Draw()
{
	VECTOR p = position - cameraPosition;
	if (alive) {
		DrawRectGraph(p.x, p.y, pattern * 64, 0, 64, 64, hImage, TRUE);
	}
	else {
		DrawRectGraph(p.x, p.y, 0, 4*64, 64, 64, hImage, TRUE);
	}
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Xは%f", position.x);
}
