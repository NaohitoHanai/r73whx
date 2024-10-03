#include "Stone.h"
#include <assert.h>
#include "Player.h"
#include "config.h"

Stone::Stone()
{
	hImage = LoadGraph("data/image/stone.png");
	assert(hImage > 0);

	position.x = 100;
	position.y = 100;

}

Stone::~Stone()
{
	DeleteGraph(hImage);
}

void Stone::Update()
{
	position.x += 5.0f;
	Player* pPlayer = FindGameObject<Player>();
	VECTOR p = position - pPlayer->GetCameraPosition();
	if (p.x > SCREEN_WIDTH) {
		DestroyMe();
	}
}

void Stone::Draw()
{
	Player* pPlayer = FindGameObject<Player>();
	VECTOR p = position - pPlayer->GetCameraPosition();
	DrawRectGraph(p.x, p.y, 0, 0, 64, 64, hImage, TRUE);
}

void Stone::SetPosition(VECTOR pos)
{
	position = pos;
}
