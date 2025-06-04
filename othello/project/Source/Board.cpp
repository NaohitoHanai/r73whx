#include "Board.h"

const int CELL_SIZE = 80;
const int DISC_RADIUS = 30;
const int LEFT = 50;
const int TOP = 10;

int lastPutX = 0; // 最後に置いたところ
int lastPutY = 0;

int sum(int n) {
	if (n == 0)
		return 0;
	int x = sum(n-1);
	return x+n;
}

Board::Board()
{
	sum(2);

	for (int y = 0; y < CELL_NUM + 2; y++) {
		for (int x = 0; x < CELL_NUM + 2; x++) {
			cells[y][x] = FREE;
		}
	}
	cells[4][4] = BLACK;
	cells[5][5] = BLACK;
	cells[4][5] = WHITE;
	cells[5][4] = WHITE;
}

Board::~Board()
{
}

void Board::Draw()
{
	DrawBox(LEFT, TOP, LEFT+CELL_SIZE*8, TOP+CELL_SIZE*8,
		GetColor(0, 128, 0), TRUE);
	for (int x = 0; x <= 8; x++) {
		DrawLine(LEFT + x * CELL_SIZE, TOP, 
				LEFT + x * CELL_SIZE, TOP + CELL_SIZE * 8,
			GetColor(0, 0, 0), 0);
	}
	for (int y = 0; y <= 8; y++) {
		DrawLine(LEFT, TOP+y*CELL_SIZE, 
				LEFT + 8 * CELL_SIZE, TOP + y*CELL_SIZE,
			GetColor(0, 0, 0), 0);
	}
	//cellsの通りに表示する
	for (int y = 0; y < CELL_NUM; y++) {
		for (int x = 0; x < CELL_NUM; x++) {
			int drawX = LEFT + CELL_SIZE/2 + x * CELL_SIZE;
			int drawY = TOP + CELL_SIZE/2 + y * CELL_SIZE;
			if (cells[y + 1][x + 1] == BLACK) {
				DrawCircle(drawX, drawY, DISC_RADIUS, GetColor(0, 0, 0), 1);
			} else if (cells[y + 1][x + 1] == WHITE) {
				DrawCircle(drawX, drawY, DISC_RADIUS, GetColor(255, 255, 255), 1);
			}
			if (x == lastPutX && y == lastPutY) {
				DrawCircle(drawX, drawY, 10, GetColor(255, 0, 0), 1);
			}
		}
	}

	int black = 0;
	int white = 0;
	for (int y = 1; y <= 8; y++) {
		for (int x = 1; x <= 8; x++) {
			switch (cells[y][x]) {
			case BLACK:
				black++;
				break;
			case WHITE:
				white++;
				break;
			}
		}
	}
	DrawFormatString(700, 400, GetColor(255,0,0),
		"黒%d : 白%d", black, white);
}



bool Board::Put(int mouseX, int mouseY, CELL_STATE color)
{
	int x = (mouseX - LEFT) / CELL_SIZE;
	if (mouseX-LEFT < 0 || x >= 8)
		return false; // 範囲外なので置けない
	int y = (mouseY - TOP) / CELL_SIZE;
	if (mouseY-TOP < 0 || y >= 8)
		return false; // 範囲外なので置けない
	if (cells[y + 1][x + 1] == FREE) {
		// ひっくり返せるか調べる
		if (CanPut(x+1, y+1, color)) {
			cells[y + 1][x + 1] = color;
			lastPutX = x;
			lastPutY = y;
			Turn(x+1, y+1, color);
			return true;
		}
	}
	return false; // すでに置いてあるので置けない
}

int Board::CanPut(int x, int y, CELL_STATE color)
{
	int get = 0;
	if (cells[y][x] != FREE)
		return 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0)
				continue;
			int n = CanPutSub(x, y, dx, dy, color);
			if (n > 0)
				get += n;
		}
	}
	return get;
	//CELL_STATE other = (color == BLACK) ? WHITE : BLACK;
	//// 右側で挟めるか調べる

	//for (int n = 1; n < 8; n++) {
	//	if (cells[y][x + n] == FREE)
	//		return false;
	//	if (cells[y][x + n] == color) {
	//		return (n>1);
	//	}
	//}
	//return false;
}

bool Board::IsPass(CELL_STATE color)
{
	// 全部のマスで置けなければtrue
	// →１つでも置ければfalse
	for (int x = 1; x <= 8; x++) {
		for (int y = 1; y <= 8; y++) {
			if (CanPut(x, y, color)) {
				return false;
			}
		}
	}
	return true;
}

int Board::CanPutSub(int x, int y, int dx, int dy, CELL_STATE color)
{
	if (cells[y+dy][x+dx] == FREE)
		return -10; // 挟んでないので終わる
	if (cells[y+dy][x+dx] == color) { // 自分なので終わる
		return 0;
	}
	// 相手の色
	return CanPutSub(x+dx, y+dy, dx, dy, color)+1; // １つ右を見る
}

void Board::Turn(int x, int y, CELL_STATE color)
{
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0)
				continue;
			TurnSub(x, y, dx, dy, color);
		}
	}
}

bool Board::TurnSub(int x, int y, int dx, int dy, CELL_STATE color)
{
	if (cells[y + dy][x + dx] == FREE)
		return false; // 挟んでないので終わる
	if (cells[y + dy][x + dx] == color) { // 自分なので終わる
		return true;
	}
	// 相手の色
	if (TurnSub(x + dx, y + dy, dx, dy, color)) {
		cells[y+dy][x+dx] = color;
		return true;
	}
	return false;
}













