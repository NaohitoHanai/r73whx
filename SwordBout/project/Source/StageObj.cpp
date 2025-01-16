#include "StageObj.h"

StageObj::StageObj(int kind, VECTOR pos, VECTOR rot, VECTOR sca)
{
	char buf[256];
	sprintf_s<256>(buf, "data/Stage/Stage_Obj%03d.mv1", kind);
	hModel = MV1LoadModel(buf);

	transform.position = pos;
	transform.rotation = rot;
	transform.scale = sca;
}

StageObj::~StageObj()
{
}
