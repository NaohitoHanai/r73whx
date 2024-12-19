#include "Camera.h"
#include "Player.h"

static const float XRotMax = DegToRad(85.0f);
static const float XRotMin = DegToRad(-45.0f);
Camera::Camera()
{
	transform.rotation.x = DegToRad(30.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetTransform().position;
	VECTOR pRot = p->GetTransform().rotation;
	VECTOR position = VGet(0,300,-300); // 仮
	VECTOR target = VGet(0,100,500); // 仮
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		transform.rotation.y += DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		transform.rotation.y -= DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		transform.rotation.x += DegToRad(3.0f);
		if (transform.rotation.x >= XRotMax) {
			transform.rotation.x = XRotMax;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		transform.rotation.x -= DegToRad(3.0f);
		if (transform.rotation.x <= XRotMin) {
			transform.rotation.x = XRotMin;
		}
	}
	VECTOR offset = VGet(0, 0, -500); // 自撮り棒
	offset = offset * MGetRotX(transform.rotation.x); // X軸回転
	offset = offset * MGetRotY(transform.rotation.y); // さらにY軸回転
	position = offset + pPos;
	target = VGet(0,150.0f, 0) + pPos;
#if 0
	// カメラの計算
	VECTOR position = VGet(0, 300.0f, -300.0f) *
		MGetRotY(transform.rotation.y) + transform.position; // カメラの位置
	VECTOR target = VGet(0, 100.0f, 500.0f) *
		MGetRotY(transform.rotation.y) + transform.position; // 注視点（カメラの見る場所）
	if (CheckHitKey(KEY_INPUT_U)) { // 上から見る用
		position = VGet(0, 1000.0f, -300.0f) *
			MGetRotY(transform.rotation.y) + transform.position; // カメラの位置
	}
#endif
	forward = VGet(0,0,1) * MGetRotY(transform.rotation.y);
	SetCameraPositionAndTarget_UpVecY(position, target);
}

VECTOR Camera::Forward()
{
	return forward;
}
