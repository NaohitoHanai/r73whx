#include "Goblin.h"
#include <assert.h>
#include "Field.h"
#include "../ImGui/imgui.h"
#include "Player.h"


Goblin::Goblin() : Goblin(VGet(0,0,0), 0)
{
}

Goblin::Goblin(VECTOR pos, float rotY)
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	assert(hModel > 0);

	anim = new Animator(hModel);
	anim->Play("data/Character/Goblin/Anim_Neutral.mv1", true);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	hWeapon = MV1LoadModel("data/Character/Weapon/Axe/Axe.mv1");
	assert(hWeapon > 0);

	state = S_IDLE;

	transform.position = pos;
	transform.rotation.y = rotY;
	basePosition = pos;
}

Goblin::~Goblin()
{
	delete anim;
}

void Goblin::Update()
{
	ImGui::Begin("GOBLIN");
	ImGui::InputInt("State", (int*)&state);
	ImGui::End();

	anim->Update();

	switch (state) {
	case S_IDLE:
		UpdateIdle();
		break;
	case S_RUN:
		UpdateRun();
		break;
	case S_ATTACK:
		UpdateAttack();
		break;
	case S_DAMAGE:
		UpdateDamage();
		break;
	}
	// �n�ʂɗ�������
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // ���������ꏊ��Ԃ��Ă��炤����
	if (field->SearchGround(transform.position + VGet(0, 1000, 0),
		transform.position + VGet(0, -1000, 0), &hitPos)) {
		transform.position = hitPos;
	}
}

void Goblin::Draw()
{
	Object3D::Draw();

	int wp = MV1SearchFrame(hModel, "hansocketR");
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hWeapon, m);
	MV1DrawModel(hWeapon);
}

bool Goblin::CheckLine(VECTOR p1, VECTOR p2)
{
	bool ret = false;
	auto hit = MV1CollCheck_Triangle(hModel, -1,
		lastP1, lastP2, p1);
	if (hit.HitNum >0) {
		ret = true;
	}
	hit = MV1CollCheck_Triangle(hModel, -1,
		p1, lastP2, p2);
	if (hit.HitNum > 0) {
		ret = true;
	}
	if (ret) {
		anim->Play("data/Character/Goblin/Anim_Damage.mv1", false);
		state = S_DAMAGE;
	}
	lastP1 = p1;
	lastP2 = p2;
	return ret;
}

void Goblin::UpdateIdle()
{
	Player* p = FindGameObject<Player>();
	if (p == nullptr) {
		return;
	}
	// Goblin�̎���̒��ɁAPlayer����������A
	VECTOR forPlayer = p->GetTransform().position - transform.position;
	if (VSize(forPlayer) > 1000) { // �������m�F
		return;
	}
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(transform.rotation.y);
	VECTOR a = VNorm(forPlayer);
	float dot = VDot(forward, a); // cos�Ƃ����߂�
	if (dot >= cos(DegToRad(30.0f))) {
		anim->Play("data/Character/Goblin/Anim_Run.mv1", true);
		state = S_RUN;
	}
}

void Goblin::UpdateRun()
{
	Player* p = FindGameObject<Player>();
	VECTOR forPlayer = p->GetTransform().position - transform.position;
	if (VSize(forPlayer) <= 150.0f) {
		anim->Play("data/Character/Goblin/Anim_Attack1.mv1", false);
		state = S_ATTACK;
	}
#if false // �p�x�o�[�W����
	// �v���C���[�ւ̃x�N�g��
	float ang = atan2(forPlayer.x, forPlayer.z); // �x�N�g���̊p�x
	float diff = ang - transform.rotation.y; // �������߂�
	//diff��-PI�`PI�̊ԂɎ��߂�
	while (diff > DX_PI) {
		diff -= DX_PI * 2.0f;// �x�ł����ƁA360���������̂Ɠ���
	}
	while (diff < -DX_PI) {
		diff += DX_PI * 2.0f;// �x�ł����ƁA360�𑫂����̂Ɠ���
	}
	if (diff > 0) { // �����̌������������̂ŁA
		transform.rotation.y += DegToRad(5.0f); // 5�x���₷
	}
	if (diff < 0) {
		transform.rotation.y -= DegToRad(5.0f); // 5�x���炷
	}
#else // ���σo�[�W����
	VECTOR right = VGet(1, 0, 0) * MGetRotY(transform.rotation.y);
	float dot = VDot(right, forPlayer);
	if (dot > 0) {
		transform.rotation.y += DegToRad(5.0f);
	}
	if (dot < 0) {
		transform.rotation.y -= DegToRad(5.0f);
	}
#endif
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(transform.rotation.y);
	transform.position += forward * 100.0f * Time::DeltaTime();

	// �[�ǂ����Ȃ��Ŗ߂�
	if (VSize(basePosition - transform.position) > 1000) {
		// ���̈ʒu���痣�ꂷ�����̂ŁAstate = S_BACK;
		state = S_BACK;
	}
}

void Goblin::UpdateAttack()
{
	if (anim->IsFinish()) {
		anim->Play("data/Character/Goblin/Anim_Neutral.mv1", true);
		state = S_IDLE;
	}
}

void Goblin::UpdateBack()
{
	// ���̈ʒu�Ɍ������Ĉړ�����
	VECTOR right = VGet(1, 0, 0) * MGetRotY(transform.rotation.y);
	VECTOR forBase = basePosition - transform.position;
	float dot = VDot(right, forBase);
	if (dot > 0) {
		transform.rotation.y += DegToRad(5.0f);
	}
	if (dot < 0) {
		transform.rotation.y -= DegToRad(5.0f);
	}
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(transform.rotation.y);
	transform.position += forward * 100.0f * Time::DeltaTime();

	// ���̈ʒu�ɕt������Astate = S_IDLE;
	if (VSize(forBase) < 100) {
		anim->Play("data/Character/Goblin/Anim_Neutral.mv1", true);
		state = S_IDLE;
	}
}

void Goblin::UpdateDamage()
{
	if (anim->IsFinish()) {
		anim->Play("data/Character/Goblin/Anim_Neutral.mv1", true);
		state = S_IDLE;
	}
}
