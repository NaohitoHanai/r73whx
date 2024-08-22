#include "Player.h"
#include <assert.h>
#include "config.h"
#include "Enemy.h"
#include "Map.h"
#include <math.h>
#include "Square.h"

static const float G = 0.5f;
static const float JUMP_H = 128;

Player::Player()
{
	hImage = LoadGraph("data/image/aoi.png");
	assert(hImage>0);
	position.x = 180;
	position.y = 300;
	pattern = 0;
	counter = 0;
	alive = true;

	cameraPosition.x = 0;
	cameraPosition.y = 0;
	
	speedY = 0.0f;
	jumping = false;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	Enemy* pEnemy = FindGameObject<Enemy>();
	VECTOR ePos = pEnemy->GetPosition();
	VECTOR d = ePos - position;
	if (VSize(d) < 32+32){
		alive = false;
	}

	Map* map = FindGameObject<Map>();
	if (alive) {
		moved = false;
		if (CheckHitKey(KEY_INPUT_D)) {
			position.x += 5;
			int push1 = map->HitCheckRight(position+VGet(45,5,0));
			int push2 = map->HitCheckRight(position + VGet(45, 62, 0));
			position.x -= max(push1, push2);
			moved = true;
//			if (position.x >= SCREEN_WIDTH - 64) {
//				position.x = SCREEN_WIDTH - 64;
//			}
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			position.x -= 5;
			int push1 = map->HitCheckLeft(position + VGet(17, 5, 0));
			int push2 = map->HitCheckLeft(position + VGet(17, 62, 0));
			position.x += max(push1, push2);
			moved = true;
			if (position.x - cameraPosition.x <= 0)
				position.x = cameraPosition.x;
		}
		if (CheckHitKey(KEY_INPUT_B)) {
			Square* p = Instantiate<Square>();
			p->SetPosition(position);
		}	
		if (jumping == false) {
			if (CheckHitKey(KEY_INPUT_N)) {
				if (recentJumpKey == false) {
					// ジャンプ開始
					speedY = -sqrt(2*G*JUMP_H);
					jumping = true;
				}
				recentJumpKey = true;
			}
			else {
				recentJumpKey = false;
			}
		}
		position.y += speedY;
		speedY += G;
		if (speedY >= 0) {
			int push1 = map->HitCheckDown(position + VGet(17, 63, 0));
			int push2 = map->HitCheckDown(position + VGet(45, 63, 0));
			int maxPush = max(push1, push2);
			if (maxPush > 0) { // 地面に付いてる
				position.y -= maxPush-1;
				speedY = 0;
				jumping = false;
			}
			else {
				jumping = true;
			}
		}
		else {
			int push1 = map->HitCheckUp(position + VGet(17, 5, 0));
			int push2 = map->HitCheckUp(position + VGet(45, 5, 0));
			int maxPush = max(push1, push2);
			if (maxPush > 0) {
				position.y += maxPush;
				speedY = 0;
			}
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
	if (alive==false) {
		DrawRectGraph(p.x, p.y, 0, 4 * 64, 64, 64, hImage, TRUE);
	}
	else if (jumping) {
		DrawRectGraph(p.x, p.y, 1 * 64, 2 * 64, 64, 64, hImage, TRUE);
	} 
	else {
		DrawRectGraph(p.x, p.y, pattern * 64, 0, 64, 64, hImage, TRUE);
	}
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Xは%f", position.x);
}

void Player::SetPosition(int x, int y)
{
	position = VGet(x, y, 0);
}
