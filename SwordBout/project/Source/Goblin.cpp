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
	// 地面に立たせる
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // 当たった場所を返してもらうため
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
	// Goblinの視野の中に、Playerが入ったら、
	VECTOR forPlayer = p->GetTransform().position - transform.position;
	if (VSize(forPlayer) > 500) { // 距離を確認
		return;
	}
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(transform.rotation.y);
	VECTOR a = VNorm(forPlayer);
	float dot = VDot(forward, a); // cosθを求める
	if (dot >= cos(DegToRad(30.0f))) {
		state = S_RUN;
	}
}

void Goblin::UpdateRun()
{
}

void Goblin::UpdateAttack()
{
}

void Goblin::UpdateDamage()
{
	if (anim->IsFinish()) {
		anim->Play("data/Character/Goblin/Anim_Neutral.mv1", true);
		state = S_IDLE;
	}
}
