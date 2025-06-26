#pragma once
//Field.h
#include "../Library/GameObject.h"
#include <vector>

class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;
private:
	void Connect(); // 接続判定
	struct CELL {
		int puyo;
		enum {
			UP = 1,
			DOWN = 2,
			LEFT = 4,
			RIGHT = 8,
		};
		int connect;
	};

	void DrawPuyo(int x, int y, CELL& cell);
	void DrawPuyo(int x, int y, int puyo);
	void CreateFallPuyo();
	bool KeyRepeat(bool pushKey, int& repeat);
	int repeatD;
	int repeatA;

	int hImage;
	static const int WIDTH = 8; // 外枠分２こ追加
	static const int HEIGHT = 14; // 外枠分２こ追加
	static const int WALL = -1;
	static const int NOPUYO = 0;
	std::vector<std::vector<CELL>> field;

	int fallPuyo[2]; // 0が親、1が子、一個の時は、[1] = NOPUYOにする
	int fallX, fallY; // 親の位置

	int rotate; // 子の付く向き（0:上、1:右、2:下、3:左）
	bool prevKey;

	float fallTimer; // 落下時間
	float fallTimerMax; // 落下時間の最大値
};