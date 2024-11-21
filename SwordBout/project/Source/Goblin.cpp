#include "Goblin.h"
#include <assert.h>
#include "Field.h"

Goblin::Goblin()
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	assert(hModel > 0);

	anim = new Animator(hModel);
	anim->Play("data/Character/Goblin/Anim_Neutral.mv1");

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	transform.position = VGet(200, 0, 100);
}

Goblin::~Goblin()
{
	delete anim;
}

void Goblin::Update()
{
	anim->Update();
	// �n�ʂɗ�������
	Field* field = FindGameObject<Field>();
	VECTOR hitPos; // ���������ꏊ��Ԃ��Ă��炤����
	if (field->SearchGround(transform.position + VGet(0, 1000, 0),
		transform.position + VGet(0, -1000, 0), &hitPos)) {
		transform.position = hitPos;
	}
}
