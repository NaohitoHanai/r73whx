#include "ActionBase.h"

ActionBase::ActionBase(Object3D* base)
{
	parent = base;
}

ActionBase::~ActionBase()
{
}

void ActionBase::Update()
{
}

void ActionBase::Suspend()
{
}

void ActionBase::Resume()
{
}
