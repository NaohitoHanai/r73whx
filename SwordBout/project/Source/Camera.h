#pragma once
#include "Object3D.h"

class Camera : public Object3D {
public:
	Camera();
	~Camera();
	void Update() override;
	// �J�����̑O�����w���x�N�g����Ԃ�
	// ���̃x�N�g���̒����͂P
	VECTOR Forward();
private:
	VECTOR forward;
	VECTOR swing;
};