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
	Player* pl = FindGameObject<Player>();
	if (pl == nullptr) {
		return;
	}
	if (got) {
		// プレイヤーに吸い込む
		// ①自分（Coin）からプレイヤーへのベクトルを作る
		VECTOR v = pl->Position() - position;
		// ②、①のベクトルの長さを、吸い込みの速度(5.0f)にする
		VECTOR v2 = VNorm(v) * gotSpeed;
		// ③、②を自分の座標に加える
		position = position + v2;
		// ④自分が、プレイヤーに近づいたら(40.0f以内)、DestroyMe()する
		if (VSize(v) - gotSpeed < 40.0f) {
			DestroyMe();
		}
		gotSpeed += 0.5f;
		return;
	}

	VECTOR plPos = pl->Position(); // プレイヤーの座標
	// 自分の座標はposition
	VECTOR diff = plPos - position;
	float len = VSize(diff);
	if (len < 200.0f) {
		got = true;
		gotSpeed = 3.0f;
	}
}

void Coin::Draw()
{
	MV1SetRotationXYZ(hModel, VGet(0, DX_PI / 2, 0));
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
