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
	//moveTarget‚ÉŒü‚©‚Á‚ÄˆÚ“®‚É‚·‚é
	Transform& tr = Parent<RedGoblin>()->transform;
	VECTOR move = moveTarget - tr.position;
	move = VNorm(move)*5.0f;
	tr.rotation.y = atan2(move.x, move.z);
	tr.position += move;
}

void ActRun::Suspend()
{
}

void ActRun::Resume()
{
	Parent<RedGoblin>()->anim->Play("data/Character/RedGoblin/Anim_Run.mv1", true);
}
