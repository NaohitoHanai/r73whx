#pragma once
//Board.h
#include "../Library/GameObject.h"

class Board : public GameObject
{
public:
	Board();
	~Board();
	void Draw() override;
	enum CELL_STATE { // �}�X�̏��
		FREE = 0,
		BLACK,
		WHITE,
	};
	bool Put(int x, int y, CELL_STATE color);
	bool CanPut(int x, int y, CELL_STATE color);
	bool IsPass(CELL_STATE color);
private:
	static const int CELL_NUM = 8;
	CELL_STATE cells[CELL_NUM+2][CELL_NUM+2];
	int CanPutSub(int x, int y, int dx, int dy, CELL_STATE color);
	void Turn(int x, int y, CELL_STATE color);
	bool TurnSub(int x, int y, int dx, int dy, CELL_STATE color);
};