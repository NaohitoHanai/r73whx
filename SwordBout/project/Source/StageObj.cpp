#include "StageObj.h"

StageObj::StageObj(int kind, VECTOR pos, VECTOR rot, VECTOR sca)
{
	char buf[256];
	sprintf_s<256>(buf, "data/Stage/Stage_Obj%03d.mv1", kind);
	hModel = MV1LoadModel(buf);
	sprintf_s<256>(buf, "data/Stage/Stage_Obj%03d_c.mv1", kind);
	hitModel = MV1LoadModel(buf);

	transform.position = pos;
	transform.rotation = rot;
	transform.scale = sca;
}

StageObj::~StageObj()
{
}

bool StageObj::SearchObject(VECTOR pos1, VECTOR pos2, VECTOR* hit)
{
	MV1SetMatrix(hitModel, transform.matrix);
	MV1RefreshCollInfo(hitModel, -1);
	MV1_COLL_RESULT_POLY ret =
		MV1CollCheck_Line(hitModel, -1, pos1, pos2);
	if (ret.HitFlag) {
		if (hit != nullptr) {
			*hit = ret.HitPosition;
		}
		return true;
	}
	return false;
}

VECTOR StageObj::CollideObject(VECTOR pos, SphereCollider col)
{
	MV1_COLL_RESULT_POLY_DIM dim = MV1CollCheck_Sphere(
		hitModel, -1, col.center+pos, col.radius);
	if (dim.HitNum==0) // �������ĂȂ��̂ŏI��
		return pos;
	for (int i = 0; i < dim.HitNum; i++) {
		VECTOR hitPos = dim.Dim[i].HitPosition;
		VECTOR hitNorm = dim.Dim[i].Normal;
	}
	return VECTOR();
}
