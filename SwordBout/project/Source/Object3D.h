#pragma once
// Object3D.h
#include "../Library/GameObject.h"

class Transform {
public:
	VECTOR position;
	VECTOR rotation;
	VECTOR scale;
};

class Object3D : public GameObject {
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;
protected: // åpè≥ÇÃîhê∂ÉNÉâÉXÇ™égÇ¶ÇÈ
	int hModel;
	Transform transform;
};
