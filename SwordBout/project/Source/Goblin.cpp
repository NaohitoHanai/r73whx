#include "Goblin.h"
#include <assert.h>
#include "Field.h"

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

	damaged = false;

	transform.position = pos;
	transform.rotation.y = rotY;
}

Goblin::~Goblin()
{
	delete anim;
}

void Goblin::Update()
{
	anim->Update();
	if (damaged) {
		if (anim->IsFinish()) {
			anim->Play("data/Character/Goblin/Anim_Neutral.mv1", true);
		}
	}
	// ’n–Ê‚É—§‚½‚¹‚é
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // “–‚½‚Á‚½êŠ‚ð•Ô‚µ‚Ä‚à‚ç‚¤‚½‚ß
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
		damaged = true;
	}
	lastP1 = p1;
	lastP2 = p2;
	return ret;
}
