#include "Board.h"

const int CELL_SIZE = 80;
const int DISC_RADIUS = 30;
const int LEFT = 50;
const int TOP = 10;

Board::Board()
{
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
	//cells‚Ì’Ê‚è‚É•\Ž¦‚·‚é
	for (int y = 0; y < CELL_NUM; y++) {
		for (int x = 0; x < CELL_NUM; x++) {
			int drawX = LEFT + CELL_SIZE/2 + x * CELL_SIZE;
			int drawY = TOP + CELL_SIZE/2 + y * CELL_SIZE;
			if (cells[y + 1][x + 1] == BLACK) {
				DrawCircle(drawX, drawY, DISC_RADIUS, GetColor(0, 0, 0), 1);
			} else if (cells[y + 1][x + 1] == WHITE) {
				DrawCircle(drawX, drawY, DISC_RADIUS, GetColor(255, 255, 255), 1);
			}
		}
	}
}

void Board::Put(int x, int y, CELL_STATE color)
{
	cells[2][3] = BLACK;
}
