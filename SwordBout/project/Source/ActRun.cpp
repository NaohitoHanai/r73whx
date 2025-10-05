#include "ActRun.h"
#include "RedGoblin.h"
ActRun::ActRun(Object3D* base) : ActionBase(base)
{
}

ActRun::~ActRun()
{
}

void ActRun::Update()
{
//	dynamic_cast<RedGoblin*>(parent)->transform
	Parent<RedGoblin>()->transform.position.z += 1.0f;
}

void ActRun::Suspend()
{
}

void ActRun::Resume()
{
	Parent<RedGoblin>()->anim->Play("data/Character/RedGoblin/Anim_Run.mv1", true);
}
