#pragma once
#include "Object3D.h"

class StageObj : public Object3D {
public:
	StageObj(int kind, VECTOR pos, VECTOR rot, VECTOR sca);
	~StageObj();
	bool SearchObject(VECTOR pos1, VECTOR pos2, VECTOR* hit = nullptr);

	/// <summary>
	/// �I�u�W�F�N�g�Ƌ��̂Ƃ̓����蔻�������
	/// </summary>
	/// <param name="pos">�����̍��W</param>
	/// <param name="col">�R���C�_�[</param>
	/// <returns>�������ĉ����Ԃ������W</returns>
	VECTOR CollideObject(VECTOR pos, SphereCollider col);
private:
	int hitModel;
};