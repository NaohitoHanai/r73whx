#include "Player.h"
#include <assert.h>
#include "config.h"
#include "Enemy.h"

Player::Player()
{
	hImage = LoadGraph("data/image/aoi.png");
	assert(hImage>0);
	x = 10;
	y = 20;
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
	float ex = pEnemy->x; // 敵のx座標
	float ey = pEnemy->y; // 敵のy座標
	// 自分の座標はx,yにあるので、当たってるか調べる
	float a = ex - x;
	float b = ey - y;
	float c = 32 + 32; // 2つの絵の半径の和
	if (a*a+b*b<c*c){
		alive = false;
	}

	if (alive) {
		moved = false;
		if (CheckHitKey(KEY_INPUT_D)) {
			x += 1;
			moved = true;
			if (x >= SCREEN_WIDTH - 64) {
				x = SCREEN_WIDTH - 64;
			}
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			x -= 1;
			moved = true;
			if (x <= 0)
				x = 0;
		}
		if (CheckHitKey(KEY_INPUT_W)) {
			y -= 1;
			moved = true;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			moved = true;
			y += 1;
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
		DrawRectGraph(x, y, pattern * 64, 0, 64, 64, hImage, TRUE);
	}
	else {
		DrawRectGraph(x, y, 0, 4*64, 64, 64, hImage, TRUE);
	}
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Xは%f", x);
}
