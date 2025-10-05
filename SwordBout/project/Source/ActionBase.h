#pragma once
#include "Object3D.h"
class ActionBase {
public:
	ActionBase(Object3D* base);
	virtual ~ActionBase();
	virtual void Update();
	virtual void Suspend();
	virtual void Resume();
protected:
	Object3D* parent;

	template<class C>
	C* Parent() {
		return dynamic_cast<C*>(parent);
	}
};