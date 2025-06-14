#pragma once
//Board.h
#include "../Library/GameObject.h"

class Board : public GameObject
{
public:
	Board();
	~Board();
	void Draw() override;
	enum CELL_STATE { // É}ÉXÇÃèÛë‘
		FREE = 0,
		BLACK,
		WHITE,
	};
	bool Put(int x, int y, CELL_STATE color);
	int CanPut(int x, int y, CELL_STATE color);
	struct IDX {
		int x, y;
		IDX(int _x, int _y) : x(_x), y(_y) {}
	};
	std::list<IDX> CanPut2(int x, int y, CELL_STATE color);
	bool IsPass(CELL_STATE color);
	CELL_STATE Get(int x, int y) { return cells[y][x]; }
private:
	static const int CELL_NUM = 8;
	CELL_STATE cells[CELL_NUM+2][CELL_NUM+2];
	int CanPutSub(int x, int y, int dx, int dy, CELL_STATE color);
	std::list<IDX> CanPutSub2(int x, int y, int dx, int dy, CELL_STATE color);
	void Turn(int x, int y, CELL_STATE color);
	bool TurnSub(int x, int y, int dx, int dy, CELL_STATE color);
};