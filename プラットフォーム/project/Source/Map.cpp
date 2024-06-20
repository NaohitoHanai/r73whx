#include "Map.h"
#include "Player.h"

int map[10][20] = {
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
};
static const int CHIP_SIZE = 64;

Map::Map()
{
	hImage = LoadGraph("data/image/bgchar.png");
}

Map::~Map()
{
}

void Map::Draw()
{
	Player* pPlayer = FindGameObject<Player>();
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 20; x++) {
			VECTOR tmp = VGet(0, 0, 0);
			tmp.x = x * CHIP_SIZE;
			tmp.y = y * CHIP_SIZE;
			VECTOR p = tmp - pPlayer->GetCameraPosition();
			if (map[y][x] == 1) {
				DrawRectGraph(p.x, p.y, 0, 32, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
			else if (map[y][x] == 2) {
				DrawRectGraph(p.x, p.y, 64, 32, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
		}
	}
}

int Map::HitCheckRight(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = map[y/CHIP_SIZE][x/CHIP_SIZE];
	if (chip > 0) {
		return x%CHIP_SIZE + 1;
	}
	return 0;
}

int Map::HitCheckLeft(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = map[y / CHIP_SIZE][x / CHIP_SIZE];
	if (chip > 0) {
		return CHIP_SIZE - x % CHIP_SIZE;
	}
	return 0;
}

int Map::HitCheckDown(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = map[y / CHIP_SIZE][x / CHIP_SIZE];
	if (chip > 0) {
		return y % CHIP_SIZE + 1;
	}
	return 0;
}

int Map::HitCheckUp(VECTOR pos)
{
	int x = pos.x;
	int y = pos.y;

	int chip = map[y / CHIP_SIZE][x / CHIP_SIZE];
	if (chip > 0) {
		return CHIP_SIZE - y % CHIP_SIZE;
	}
	return 0;
}
