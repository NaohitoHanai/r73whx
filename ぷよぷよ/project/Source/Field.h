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
	void DrawPuyo(int x, int y, int puyo);
	void CreateFallPuyo();
	bool KeyRepeat(bool pushKey, int& repeat);
	int repeatD;
	int repeatA;

	int hImage;
	static const int WIDTH = 8; // �O�g���Q���ǉ�
	static const int HEIGHT = 14; // �O�g���Q���ǉ�
	static const int WALL = -1;
	static const int NOPUYO = 0;
	struct CELL {
		int puyo;
	};
	std::vector<std::vector<CELL>> field;

	int fallPuyo[2]; // 0���e�A1���q�A��̎��́A[1] = NOPUYO�ɂ���
	int fallX, fallY; // �e�̈ʒu

	int rotate; // �q�̕t�������i0:��A1:�E�A2:���A3:���j
	bool prevKey;

	float fallTimer; // ��������
	float fallTimerMax; // �������Ԃ̍ő�l
};