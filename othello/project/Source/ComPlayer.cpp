#include "ComPlayer.h"

ComPlayer::ComPlayer(Board::CELL_STATE color) : Player(color)
{
	waitTimer = 0.5f;
}

ComPlayer::~ComPlayer()
{
}

static int Score[8][8] = {
	{100,1,50,50,50,50,1,100},
	{ 1, 1,1,1,1,1,1,1},
	{ 50,1,80,1,1,80,1,50},
	{ 50,1,1,1,1,1,1,50},
	{ 50,1,1,1,1,1,1,50},
	{ 50,1,80,1,1,80,1,50},
	{  1,1,1,1,1,1,1,1},
	{100,1,50,50,50,50,1,100},
};

void ComPlayer::Update()
{
	if (!active)
		return;

	Board* bo = FindGameObject<Board>();

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			evalPoint[y][x] = 0;
		}
	}

	// 評価点の計算をする→evalPointに代入する
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			int n = bo->CanPut(x + 1, y + 1, myColor);
			if (n > 0) {
				evalPoint[y][x] += Score[y][x];
			}
		}
	}

	waitTimer -= Time::DeltaTime();
	if (waitTimer > 0)
		return;
	waitTimer = 0.5f;

	// 一番大きな点のマスを求めて、
	// そこに置く
	int px = 0, py = 0;
	int max = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (evalPoint[y][x] > max) {
				// 最大の場所を探す
				max = evalPoint[y][x];
				px = x;
				py = y;
			}
		}
	}
	if (bo->Put(px*80+100, py*80+60, myColor)) {
		active = false; // 自分のターン終わり
		return;
	}
}

void ComPlayer::Draw()
{
	if (!active)
		return;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			DrawFormatString(
				x * 80 + 50, y * 80 + 10,
				GetColor(255, 255, 255),
				"%d", evalPoint[y][x]);
		}
	}
}