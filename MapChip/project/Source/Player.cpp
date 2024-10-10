#include "Player.h"

Player::Player()
{
	position = VGet(0, 0, -500.0f);
}

Player::Player(VECTOR pos)
{
	position = pos;
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawSphere3D(position, 50.0f, 20,
		GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}
