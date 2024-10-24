#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
}

Coin::Coin(VECTOR pos)
{
	position = pos;
	hModel = MV1LoadModel("data/coin.mv1");
	got = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	if (got) {
		// プレイヤーに吸い込む

		return;
	}

	Player* pl = FindGameObject<Player>();
	if (pl == nullptr) {
		return;
	}
	VECTOR plPos = pl->Position(); // プレイヤーの座標
	// 自分の座標はposition
	VECTOR diff = plPos - position;
	float len = VSize(diff);
	if (len < 100.0f) {
		got = true;
	}
}

void Coin::Draw()
{
	MV1SetRotationXYZ(hModel, VGet(0, DX_PI / 2, 0));
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
