#include "Map.h"
#include "Player.h"

int map[10][20] = {
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1 },
	{ 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
};

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
			tmp.x = x * 64;
			tmp.y = y * 64;
			VECTOR p = tmp - pPlayer->GetCameraPosition();
			if (map[y][x] == 1) {
				DrawRectGraph(p.x, p.y, 0, 32, 64, 64, hImage, TRUE);
			}
			else if (map[y][x] == 2) {
				DrawRectGraph(p.x, p.y, 64, 32, 64, 64, hImage, TRUE);
			}
		}
	}
}
