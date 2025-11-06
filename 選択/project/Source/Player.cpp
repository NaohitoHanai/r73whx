#include "Player.h"
#include "Field.h"

Player::Player()
{
}

Player::Player(VECTOR pos)
{
	position = pos;
}

Player::~Player()
{
}

// 0`1‚ğó‚¯æ‚èA0`1‚Å•Ô‚·ŠÖ”
float convRate(float time) {
	if (time < 0.5f) {
		return time * 2.0f;
	}
	else if (time < 0.75f) {
		return 1.0f - (time - 0.5f);
	}
	else {
		return time;
	}
}

VECTOR lerp(VECTOR start, VECTOR end, float timeRate) {
	float moveRate = convRate(timeRate);
	return (end - start) * moveRate + start;
}

void Player::Update()
{
	if (frameCounter < totalFrame) {
		frameCounter++;
		float t = (float)frameCounter / totalFrame; // ŠÔŠ„‡
		position = lerp(start, goal, t);
		return;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		MoveTo(VGet(100, 0, 0));
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		MoveTo(VGet(-100, 0, 0));
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		MoveTo(VGet(0, 0, 100));
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		MoveTo(VGet(0, 0, -100));
	}
}

void Player::Draw()
{
	DrawSphere3D(position, 50.0f, 20,
		GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}

void Player::MoveTo(VECTOR move)
{
	Field* f = FindGameObject<Field>();
	if (f->IsWallBlock(position + move) == false) {
		start = position;
		goal = position + move;
		frameCounter = 0;
		totalFrame = 30;
	}
}
