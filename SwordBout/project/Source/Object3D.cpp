#include "Object3D.h"

Object3D::Object3D()
{
	hModel = -1;
	transform.position = VGet(0, 0, 0);
	transform.rotation = VGet(0, 0, 0);
	transform.scale = VGet(1, 1, 1);
}

Object3D::~Object3D()
{
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	MV1SetPosition(hModel, transform.position);
	MV1SetRotationXYZ(hModel, transform.rotation);
	MV1DrawModel(hModel);
}
