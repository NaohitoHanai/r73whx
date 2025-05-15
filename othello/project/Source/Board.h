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
	void Put(int x, int y, CELL_STATE color);
private:
	static const int CELL_NUM = 8;
	CELL_STATE cells[CELL_NUM+2][CELL_NUM+2];
};