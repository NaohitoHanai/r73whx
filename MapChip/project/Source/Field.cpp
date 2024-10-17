#include "Field.h"
#include "Player.h"

const int MapX = 8;
const int MapZ = 4;
int map[MapZ][MapX] = {
	{ 1,1,0,1,1,1,0,1 },
	{ 1,0,0,0,0,0,0,1 },
	{ 1,1,0,1,1,9,0,1 },
	{ 1,1,0,1,1,1,1,1 },
};

Field::Field()
{
	hModel = MV1LoadModel("data/wallEarth01.mv1");
	rotation = VGet(0, DegToRad(90.0f), 0);
	// mapデータを調べて、9があれば、new Player()する
	for (int z = 0; z < MapZ; z++) {
		for (int x = 0; x < MapX; x++) {
			if (map[z][x] == 9) {
				new Player(VGet(x*100.0f, 50.0f, z*-100.0f));
			}
		}
	}
}

Field::~Field()
{
}

void Field::Update()
{
}

void Field::Draw()
{
	MV1SetRotationXYZ(hModel, rotation);
	for (int z = 0; z < MapZ; z++) {
		for (int x = 0; x < MapX; x++) {
			if (map[z][x] == 1) {
				MV1SetPosition(hModel, VGet(x * 100.0f, 0, z * -100.0f));
				MV1DrawModel(hModel);
			}
		}
	}
}

bool Field::IsWallBlock(VECTOR pos)
{
	int x = (int)((pos.x + 50.0f) / 100.0f);
	int z = (int)((50.0f - pos.z) / 100.0f);
	if (map[z][x] == 1) {
		return true;
	}
	return false;
}