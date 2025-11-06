#include "Field.h"
#include "Player.h"
#include "Coin.h"
#include <vector>

//const int MapX = 8;
//const int MapZ = 4;
std::vector<std::vector<int>> map = {
	{ 1,1,0,1,1,1,0,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,0,1,1,9,0,1,1,1,1,1 },
	{ 1,1,2,1,1,1,1,1 },
	{ 1,1,2,1,1,1,1,1 },
	{ 1,1,0,1,1,1,1,1 },
	{ 1,1,0,1,1,1,1,1 },
	{ 1,1,0,1,1,1,1,1 },
};

//std::vector<int> red; // 可変長配列

Field::Field()
{
//	red.push_back(5); // 要素を増やす
//	red.push_back(10);
//	red.push_back(12);
//	red.push_back(18);
//	for (int i = 0; i < red.size(); i++) { // vectorの要素数は.size()でわかる
//		red[i] = 0;
//	}

	hModel = MV1LoadModel("data/wallEarth01.mv1");
	rotation = VGet(0, DegToRad(90.0f), 0);
	// mapデータを調べて、9があれば、new Player()する
	for (int z = 0; z < map.size(); z++) {
		std::vector<int> line = map[z];
		for (int x = 0; x < line.size(); x++) {
			if (map[z][x] == 9) {
				new Player(VGet(x*100.0f, 50.0f, z*-100.0f));
			}
			if (map[z][x] == 2) {
				new Coin(VGet(x * 100.0f, 50.0f, z * -100.0f));
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
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
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