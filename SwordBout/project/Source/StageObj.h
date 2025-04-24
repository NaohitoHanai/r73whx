#pragma once
#include "Object3D.h"

class StageObj : public Object3D {
public:
	StageObj(int kind, VECTOR pos, VECTOR rot, VECTOR sca);
	~StageObj();
	bool SearchObject(VECTOR pos1, VECTOR pos2, VECTOR* hit = nullptr);

	/// <summary>
	/// オブジェクトと球体との当たり判定をする
	/// </summary>
	/// <param name="pos">自分の座標</param>
	/// <param name="col">コライダー</param>
	/// <returns>当たって押し返した座標</returns>
	VECTOR CollideObject(VECTOR pos, SphereCollider col);
private:
	int hitModel;
};