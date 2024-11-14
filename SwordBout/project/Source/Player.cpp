#include "Player.h"
#include <assert.h>
#include "Field.h"

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
		//    ����ĂȂ��Ƃ��ɐi�ރx�N�g�� * Y����]�s��(�p�x)
		transform.position += velocity;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		transform.rotation.y += 3.0f * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		transform.rotation.y -= 3.0f * DX_PI_F / 180.0f;
	}
	// �n�ʂɗ�������
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // ���������ꏊ��Ԃ��Ă��炤����
	if (field->SearchGround(transform.position + VGet(0, 1000, 0),
			transform.position + VGet(0, -1000, 0), &hitPos)) {
		transform.position = hitPos;
	}

	// �J�����̌v�Z
	VECTOR position = VGet(0, 300.0f, -300.0f)*
			MGetRotY(transform.rotation.y) + transform.position; // �J�����̈ʒu
	VECTOR target = VGet(0, 100.0f, 500.0f) *
			MGetRotY(transform.rotation.y) + transform.position; // �����_�i�J�����̌���ꏊ�j
	SetCameraPositionAndTarget_UpVecY(position, target);
}
