#pragma once
#include "Object3D.h"

//�C���^�[�t�F�[�X�N���X
class ActionBase {
public:
	ActionBase(Object3D* base) { parent = base; }
	// �C���^�[�t�F�[�X�i���������֐���p�ӂ��Ăˁj
	virtual ~ActionBase() {}
	virtual void Update() {}
	virtual void Suspend() {} // ���f
	virtual void Resume() {} // �ĊJ
	virtual bool IsFinish() {return false;}
	virtual bool EnableCancel() {return true;}

protected:
	Object3D* parent;

	template<class C>
	C* Parent() {
		return dynamic_cast<C*>(parent);
	}
};