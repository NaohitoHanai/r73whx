#include "ActAttack.h"
#include "RedGoblin.h"

ActAttack::ActAttack(Object3D* base) : ActionBase(base)
{
}

ActAttack::~ActAttack()
{
}

void ActAttack::Update()
{
}

void ActAttack::Suspend()
{
}

void ActAttack::Resume()
{
	Parent<RedGoblin>()->anim->Play(
		"data/Character/RedGoblin/Anim_Attack1.mv1", false);

}

bool ActAttack::IsFinish()
{
	return Parent<RedGoblin>()->anim->IsFinish();
}

bool ActAttack::EnableCancel()
{
	return false;
}
