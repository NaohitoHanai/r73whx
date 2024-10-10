#include "Field.h"
#include "Player.h"

const int MapX = 8;
const int MapZ = 4;
int map[MapZ][MapX] = {
	{ 1,1,0,1,1,1,0,1 },
	{ 1,0,0,0,0,0,0,1 },
	{ 1,1,0,1,1,9,1,1 },
	{ 1,1,0,1,1,1,1,1 },
};

Field::Field()
{
	hModel = MV1LoadModel("data/wallEarth01.mv1");
	rotation = VGet(0, 90.0f / 180.0f * DX_PI_F, 0);
	// mapデータを調べて、9があれば、new Player()する
	for (int z = 0; z < MapZ; z++) {
		for (int x = 0; x < MapX; x++) {
			if (map[z][x] == 9) {
				new Player(VGet(0, 50.0f, -300));
			}
		}
	}
}

//問題
// 左手法で、X+を右、Y+を上にしたとき、Z-はどっちか


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