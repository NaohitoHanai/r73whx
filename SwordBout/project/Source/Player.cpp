#include "Player.h"
#include <assert.h>

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	assert(hModel > 0);
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));
}

Player::~Player()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_W)) {
//		transform.position.z += 2.0f * cosf(transform.rotation.y);
//		transform.position.x += 2.0f * sinf(transform.rotation.y);
		VECTOR velocity = VGet(0,0,2) * MGetRotY(transform.rotation.y);
		transform.position += velocity;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		transform.rotation.y += 3.0f * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		transform.rotation.y -= 3.0f * DX_PI_F / 180.0f;
	}
}
