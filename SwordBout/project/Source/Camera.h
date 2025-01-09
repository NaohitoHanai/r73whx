#pragma once
#include "Object3D.h"

class Camera : public Object3D {
public:
	Camera();
	~Camera();
	void Update() override;
	// カメラの前方を指すベクトルを返す
	// このベクトルの長さは１
	VECTOR Forward();
private:
	VECTOR forward;
	VECTOR swing;
};