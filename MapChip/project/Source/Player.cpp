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

VECTOR ease(VECTOR start, VECTOR end, float timeRate) {
	float moveRate = convRate(timeRate);
	return (end - start) * moveRate + start;
}

void Player::Update()
{
	if (frameCounter < totalFrame) {
		frameCounter++;
		float t = (float)frameCounter / totalFrame; // ŽžŠÔŠ„‡
		position = ease(start, goal, t);
		return;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		Field* f = FindGameObject<Field>();
		if (f->IsWallBlock(position+VGet(100,0,0)) == false) {
			start = position;
			goal = position + VGet(100, 0, 0);
			frameCounter = 0;
			totalFrame = 30;
		}
	}
}

void Player::Draw()
{
	DrawSphere3D(position, 50.0f, 20,
		GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}
