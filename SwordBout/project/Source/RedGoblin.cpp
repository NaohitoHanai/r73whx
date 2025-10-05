#include "RedGoblin.h"
#include <assert.h>
#include "ActAttack.h"
#include "ActRun.h"

RedGoblin::RedGoblin()
{
}

RedGoblin::RedGoblin(VECTOR pos, float rotY)
{
	hModel = MV1LoadModel("data/Character/RedGoblin/RedGoblin.mv1");
	assert(hModel > 0);

	anim = new Animator(hModel);
	anim->Play("data/Character/RedGoblin/Anim_Neutral.mv1", true);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	hWeapon = MV1LoadModel("data/Character/Weapon/Sword/Sword.mv1");
	assert(hWeapon > 0);

	transform.position = pos;
	transform.rotation.y = rotY;

	actions[ActID::A_ATTACK] = new ActAttack(this);
	actions[ActID::A_RUN] = new ActRun(this);
	actID = ActID::A_RUN;
	actions[actID]->Resume();
}

RedGoblin::~RedGoblin()
{
}

void RedGoblin::Update()
{
	anim->Update();
	actions[actID]->Update();
}

void RedGoblin::Draw()
{
	Object3D::Draw();

	int wp = MV1SearchFrame(hModel, "hansocketR");
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hWeapon, m);
	MV1DrawModel(hWeapon);
}

bool RedGoblin::CheckLine(VECTOR p1, VECTOR p2)
{
	return false;
}

void RedGoblin::ChangeAction(ActID act)
{
	actions[actID]->Suspend();
	actions[act]->Resume();
	actID = act;
}
