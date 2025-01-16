#pragma once
#include "Object3D.h"

class StageObj : public Object3D {
public:
	StageObj(int kind, VECTOR pos, VECTOR rot, VECTOR sca);
	~StageObj();
};