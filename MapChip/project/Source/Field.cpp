#include "Field.h"

Field::Field()
{
	hModel = MV1LoadModel("data/wallEarth01.mv1");
	rotation = VGet(0, 90.0f / 180.0f * DX_PI_F, 0);
}

Field::~Field()
{
}

void Field::Update()
{
	rotation.y += 0.1f;
}

void Field::Draw()
{
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}