#include "Player.h"
#include "Board.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Update()
{
	// ƒ}ƒEƒX‚Ì“ü—Í
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		Board* bo = FindGameObject<Board>();
		bo->Put(mouseX, mouseY, Board::BLACK);
	}
}

void Player::Draw()
{
}
