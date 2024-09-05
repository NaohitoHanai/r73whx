#include "Map.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include <assert.h>

//static const int WIDTH = 30;
//static const int HEIGHT = 10;
//// -1:敵、-2:アイテム
//int map[HEIGHT][WIDTH] = {
//	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 0, 0,-2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-2, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 0, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,-2, 0, 0, 0,-1, 0, 0 },
//	{ 1,-9, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
//};
static const int CHIP_SIZE = 64;

Map::Map()
{
	hImage = LoadGraph("data/image/bgchar.png");
	assert(hImage >= 0);
	csv = new CsvReader("data/map1.csv");
	assert(csv->GetLines() > 0);
}

Map::~Map()
{
	DeleteGraph(hImage);
}

void Map::Start()
{
	for (int y = 0; y < csv->GetLines(); y++) {
		for (int x = 0; x < csv->GetColumns(y); x++) {
			if (csv->GetInt(y, x) == -1) {
				Item* it = Instantiate<Item>();
				it->SetPosition(x * CHIP_SIZE, y * CHIP_SIZE);
			}
			else if (csv->GetInt(y, x) == -2) {
				Enemy* e = Instantiate<Enemy>();
				e->SetPosition(x * CHIP_SIZE, y * CHIP_SIZE);
			}
			else if (csv->GetInt(y, x) == -9) {
				Player* p = FindGameObject<Player>();
				p->SetPosition(x * CHIP_SIZE, y * CHIP_SIZE);
			}
		}
	}
}

void Map::Draw()
{
	Player* pPlayer = FindGameObject<Player>();
	for (int y = 0; y < csv->GetLines(); y++) {
		for (int x = 0; x < csv->GetColumns(y); x++) {
			VECTOR tmp = VGet(0, 0, 0);
			tmp.x = x * CHIP_SIZE;
			tmp.y = y * CHIP_SIZE;
			VECTOR p = tmp - pPlayer->GetCameraPosition();
			if (csv->GetInt(y, x) == 1) {
				DrawRectGraph(p.x, p.y, 0, 32, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
			else if (csv->GetInt(y, x) == 2) {
				DrawRectGraph(p.x, p.y, 64, 32, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
		}
	}
}

int Map::HitCheckRight(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = csv->GetInt(y/CHIP_SIZE, x/CHIP_SIZE);
	if (chip > 0) {
		return x%CHIP_SIZE + 1;
	}
	return 0;
}

int Map::HitCheckLeft(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = csv->GetInt(y / CHIP_SIZE, x / CHIP_SIZE);
	if (chip > 0) {
		return CHIP_SIZE - x % CHIP_SIZE;
	}
	return 0;
}

int Map::HitCheckDown(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = csv->GetInt(y / CHIP_SIZE, x / CHIP_SIZE);
	if (chip > 0) {
		return y % CHIP_SIZE + 1;
	}
	return 0;
}

int Map::HitCheckUp(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = csv->GetInt(y / CHIP_SIZE, x / CHIP_SIZE);
	if (chip > 0) {
		return CHIP_SIZE - y % CHIP_SIZE;
	}
	return 0;
}
