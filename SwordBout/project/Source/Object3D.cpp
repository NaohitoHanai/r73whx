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
	MATRIX scale = MGetScale(transform.scale);
	MATRIX rotX = MGetRotX(transform.rotation.x); // 回転行列Pitch
	MATRIX rotY = MGetRotY(transform.rotation.y); // 回転行列Yaw
	MATRIX rotZ = MGetRotZ(transform.rotation.z); // 回転行列Roll
	MATRIX trans = MGetTranslate(transform.position); // 移動行列
	MATRIX mat = scale * rotZ * rotX * rotY * trans;
	MV1SetMatrix(hModel, mat);
	MV1DrawModel(hModel);
}
