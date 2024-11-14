#pragma once
// Field.h
#include "Object3D.h"

class Field : public Object3D {
public:
	Field();
	~Field();
	void Update() override;

	/// <summary>
	/// �n�ʂ�Ray�̓����蔻�������
	/// </summary>
	/// <param name="pos1">Ray�̎n�_</param>
	/// <param name="pos2">Ray�̏I�_</param>
	/// <param name="hit">�����������W��Ԃ�</param>
	/// <returns>�������Ă����true</returns>
	bool SearchGround(VECTOR pos1, VECTOR pos2, VECTOR* hit = nullptr);
};