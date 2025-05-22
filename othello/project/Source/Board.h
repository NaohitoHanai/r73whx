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
private:
	static const int CELL_NUM = 8;
	CELL_STATE cells[CELL_NUM+2][CELL_NUM+2];
	bool CanPut(int x, int y, CELL_STATE color);
	int CanPutSub(int x, int y, int dx, int dy, CELL_STATE color);
	void Turn(int x, int y, CELL_STATE color);
	bool TurnSub(int x, int y, int dx, int dy, CELL_STATE color);
};