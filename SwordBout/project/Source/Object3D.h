#pragma once
// Object3D.h
#include "../Library/GameObject.h"

class Transform {
public:
	VECTOR position;
	VECTOR rotation;
	VECTOR scale;
	MATRIX matrix; // í«â¡
};

class SphereCollider {
public:
	VECTOR center;
	float radius;
	SphereCollider(VECTOR c, float r) {
		center = c;
		radius = r;
	}
};

class Object3D : public GameObject {
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;
	Transform GetTransform() {
		return transform;
	}
protected: // åpè≥ÇÃîhê∂ÉNÉâÉXÇ™égÇ¶ÇÈ
	int hModel;
	Transform transform;
	SphereCollider* collider;
};
