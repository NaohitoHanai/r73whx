#pragma once
#include "Object3D.h"

//インターフェースクラス
class ActionBase {
public:
	ActionBase(Object3D* base) { parent = base; }
	// インターフェース（こういう関数を用意してね）
	virtual ~ActionBase() {}
	virtual void Update() {}
	virtual void Suspend() {} // 中断
	virtual void Resume() {} // 再開
	virtual bool IsFinish() {return false;}
	virtual bool EnableCancel() {return true;}

protected:
	Object3D* parent;

	template<class C>
	C* Parent() {
		return dynamic_cast<C*>(parent);
	}
};