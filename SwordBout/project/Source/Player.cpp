#include "Player.h"
#include <assert.h>
#include "Field.h"

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	assert(hModel > 0);

	hWeapon = MV1LoadModel("data/Character/Weapon/Sabel/Sabel.mv1");
	assert(hWeapon > 0);

	anim = new Animator(hModel);
	anim->Play("data/Character/Player/Anim_Run.mv1");

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));
#if 0
	armRot = 0.0f;
#endif
}

Player::~Player()
{
	delete anim;
}

void Player::Update()
{
	anim->Update();
	if (CheckHitKey(KEY_INPUT_W)) {
//		transform.position.z += 2.0f * cosf(transform.rotation.y);
//		transform.position.x += 2.0f * sinf(transform.rotation.y);
		VECTOR velocity = VGet(0,0,2) * MGetRotY(transform.rotation.y);
		//    回ってないときに進むベクトル * Y軸回転行列(角度)
		transform.position += velocity;
		anim->Play("data/Character/Player/Anim_Run.mv1");
	}
	else {
		anim->Play("data/Character/Player/Anim_Neutral.mv1");
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		transform.rotation.y += 3.0f * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		transform.rotation.y -= 3.0f * DX_PI_F / 180.0f;
	}
	// 地面に立たせる
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // 当たった場所を返してもらうため
	if (field->SearchGround(transform.position + VGet(0, 1000, 0),
			transform.position + VGet(0, -1000, 0), &hitPos)) {
		transform.position = hitPos;
	}

	// カメラの計算
	VECTOR position = VGet(0, 300.0f, -300.0f)*
			MGetRotY(transform.rotation.y) + transform.position; // カメラの位置
	VECTOR target = VGet(0, 100.0f, 500.0f) *
			MGetRotY(transform.rotation.y) + transform.position; // 注視点（カメラの見る場所）
	SetCameraPositionAndTarget_UpVecY(position, target);

#if 0
	/** 骨をいじる実験 **/
	armRot += DegToRad(3.0f);
	int armID = MV1SearchFrame(hModel, "armL");
	MATRIX mrotA = MGetRotY(armRot);
	MATRIX mtransA = MGetTranslate(VGet(13.05, 0, 0));
	MV1SetFrameUserLocalMatrix(hModel, armID, mrotA*mtransA);
	int elbowID = MV1SearchFrame(hModel, "elbowL");
	MATRIX mrot = MGetRotY(-DX_PI_F / 2);
	MATRIX mtrans = MGetTranslate(VGet(28.5*2, 0, 0));
	MV1SetFrameUserLocalMatrix(hModel, elbowID, mrot*mtrans);
#endif
}

void Player::Draw()
{
	Object3D::Draw(); //継承元の関数を呼ぶ

	int wp = MV1SearchFrame(hModel, "wp");
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hWeapon, m);
	MV1DrawModel(hWeapon);
}
