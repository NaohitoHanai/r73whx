#include "Player.h"
#include <assert.h>
#include "Field.h"
#include "Goblin.h"
#include "Camera.h"

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	assert(hModel > 0);

	hWeapon = MV1LoadModel("data/Character/Weapon/Sabel/Sabel.mv1");
	assert(hWeapon > 0);

	anim = new Animator(hModel);
	anim->Play("data/Character/Player/Anim_Run.mv1", true);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));
#if 0
	armRot = 0.0f;
#endif
	state = S_STOP;
}

Player::~Player()
{
	delete anim;
}

void Player::Update()
{
	anim->Update();
	// ���������́A�ǂ̏�Ԃł���鏈��
	switch (state) { // ��Ԃɂ���āA������U�蕪����
	case S_STOP:
		UpdateStop();
		break;
	case S_ATTACK1:
		UpdateAttack1();
		break;
	case S_ATTACK2:
		UpdateAttack2();
		break;
	case S_ATTACK3:
		UpdateAttack3();
		break;
	}
	// �������牺�́A�ǂ̏�Ԃł���鏈��
	// �G�Ƃ̓����蔻�������
	auto goblins = FindGameObjects<Goblin>();
	for (Goblin* g : goblins) {
		VECTOR gPos = g->GetTransform().position;
		VECTOR vec = gPos - transform.position;
		vec.y = 0; // �����͖�������
		if (VSize(vec) < 100.0f) {
			float pushVal = 100.f - VSize(vec);
			transform.position -= VNorm(vec)* pushVal; // �����Ԃ��x�N�g��
		}
	}

	// �n�ʂɗ�������
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // ���������ꏊ��Ԃ��Ă��炤����
	if (field->SearchGround(transform.position + VGet(0, 1000, 0),
			transform.position + VGet(0, -1000, 0), &hitPos)) {
		transform.position = hitPos;
	}

#if 0
	/** ������������� **/
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
	Object3D::Draw(); //�p�����̊֐����Ă�

	int wp = MV1SearchFrame(hModel, "wp");
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hWeapon, m);
	MV1DrawModel(hWeapon);

	DrawLine3D(VGet(0,0,0) * m, VGet(0, -100, 0) * m, GetColor(255, 0, 0));
}

void Player::UpdateStop()
{
	Camera* c = FindGameObject<Camera>();
	// D����������E�֐i�ށAA���������獶�֐i��
	//* �i�񂾕����������āA����A�j���[�V����
	// W��D�𓯎�����������A�΂߂ɑ��x10�œ���
	//* WASD�������Ȃ���΁A�ړ������ɑҋ@�A�j���[�V����
		// ���͂̃x�N�g�������i�����͂P�j
	VECTOR inputDir = VGet(0, 0, 0); // ���͕���
	if (CheckHitKey(KEY_INPUT_W)) {
		inputDir.z = 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		inputDir.x = 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		inputDir.x = -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		inputDir.z = -1.0f;
	}
	if (VSize(inputDir)>0) {
		inputDir = VNorm(inputDir); // �������P�ɂ���
		// �ړ��x�N�g�������̓x�N�g���~�J�����̉�]�~���x
		VECTOR velocity = inputDir * MGetRotY(c->GetTransform().rotation.y) * 10.0f;
		// ���W �{�� �ړ��x�N�g��
		transform.position += velocity;
		// �L�����̌����́A�ړ��x�N�g�����狁�߂�
		transform.rotation.y = atan2f(velocity.x, velocity.z);
		anim->Play("data/Character/Player/Anim_Run.mv1", true);
	}
	else {
		anim->Play("data/Character/Player/Anim_Neutral.mv1", true);
	}

	if (CheckHitKey(KEY_INPUT_D)) {
		transform.rotation.y += 3.0f * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		transform.rotation.y -= 3.0f * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_M)) { // �U��
		anim->Play("data/Character/Player/Anim_Attack1.mv1", false);
		state = S_ATTACK1;
	}
}

void Player::UpdateAttack1()
{
	if (anim->IsFinish()) {
		state = S_STOP;
	}
	if (anim->CurrentAnimTime() > 8.5f) {
		if (CheckHitKey(KEY_INPUT_M)) { // �U��
			anim->Play("data/Character/Player/Anim_Attack2.mv1", false);
			state = S_ATTACK2;
		}
	}
	AttackEnemy();
}

void Player::UpdateAttack2()
{
	if (anim->IsFinish()) {
		state = S_STOP;
	}
	if (anim->CurrentAnimTime() > 8.5f) {
		if (CheckHitKey(KEY_INPUT_M)) { // �U��
			anim->Play("data/Character/Player/Anim_Attack3.mv1", false);
			state = S_ATTACK3;
		}
	}
	AttackEnemy();
}

void Player::UpdateAttack3()
{
	if (anim->IsFinish()) {
		state = S_STOP;
	}
	AttackEnemy();
}

void Player::AttackEnemy()
{
	int wp = MV1SearchFrame(hModel, "wp");
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hWeapon, m);
	MV1DrawModel(hWeapon);

	auto goblins = FindGameObjects<Goblin>();
	for (Goblin* g : goblins) {
		g->CheckLine(VGet(0,0,0)*m, VGet(0,-100,0)*m);
	}
}
