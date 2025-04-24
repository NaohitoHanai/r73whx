#include "Object3D.h"

Object3D::Object3D()
{
	hModel = -1;
	transform.position = VGet(0, 0, 0);
	transform.rotation = VGet(0, 0, 0);
	transform.scale = VGet(1, 1, 1);
	collider = nullptr;
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
	MATRIX rotX = MGetRotX(transform.rotation.x); // ��]�s��Pitch
	MATRIX rotY = MGetRotY(transform.rotation.y); // ��]�s��Yaw
	MATRIX rotZ = MGetRotZ(transform.rotation.z); // ��]�s��Roll
	MATRIX trans = MGetTranslate(transform.position); // �ړ��s��
	transform.matrix = scale * rotZ * rotX * rotY * trans;
	MV1SetMatrix(hModel, transform.matrix);
	MV1DrawModel(hModel);
	if (collider != nullptr) {
		DrawSphere3D(collider->center+transform.position, collider->radius, 20, 
				GetColor(255,0,0), GetColor(255,0,0), FALSE);
	}
}
