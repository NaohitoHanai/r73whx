#include "Player.h"
#include "Board.h"

Player::Player(Board::CELL_STATE color)
{
	myColor = color;
	active = false;
}

Player::~Player()
{
}

void Player::Update()
{
	if (!active)
		return;

	// マウスの入力
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		Board* bo = FindGameObject<Board>();
		if (bo->Put(mouseX, mouseY, myColor)) {
			active = false; // 自分のターン終わり
		}
	}
}

void Player::Draw()
{
}

void Player::TurnStart()
{
	active = true;
}

bool Player::TurnEnded()
{
	return active == false;
}
