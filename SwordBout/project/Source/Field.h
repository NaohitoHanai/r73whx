#pragma once
// Field.h
#include "Object3D.h"

class Field : public Object3D {
public:
	Field();
	~Field();
	void Update() override;
};