#include "Field.h"
#include <assert.h>
#include "../ImGui/imgui.h"

Field::Field()
{
	field.resize(HEIGHT);
	for (int y = 0; y < HEIGHT; y++) {
		field[y].resize(WIDTH);
		for (int x = 0; x < WIDTH; x++) {
			if (x == 0 || x == WIDTH - 1)
				field[y][x].puyo = WALL;
			else
				field[y][x].puyo = NOPUYO;
		}
	}
	for (int x = 0; x < WIDTH; x++) {
		field[0][x].puyo = -1;
	}
	CreateFallPuyo();

	hImage = LoadGraph("data/puyo_sozai.png");
	assert(hImage>0);

	prevKey = true;
	rotate = 3;

	fallTimerMax = 1.0f;
	fallTimer = fallTimerMax;
}

Field::~Field()
{
}

void Field::Update()
{
	int fallX1 = cosf(rotate * DX_PI_F / 2);
	int fallY1 = sinf(rotate * DX_PI_F / 2);
	fallX1 = fallX + fallX1;
	fallY1 = fallY - fallY1;
	if (fallPuyo[1] != NOPUYO) {
		if (KeyRepeat(CheckHitKey(KEY_INPUT_D), repeatD)) {
			if (field[fallY][fallX + 1].puyo == NOPUYO &&
				field[fallY1][fallX1 + 1].puyo == NOPUYO) {
				fallX += 1;
			}
		}
		if (KeyRepeat(CheckHitKey(KEY_INPUT_A), repeatA)) {
			if (field[fallY][fallX - 1].puyo == NOPUYO &&
				field[fallY1][fallX1 - 1].puyo == NOPUYO) {
				fallX -= 1;
			}
		}
	}
	fallTimer -= Time::DeltaTime();
	if (CheckHitKey(KEY_INPUT_S))
		fallTimer = 0;
	if (fallTimer <= 0) {
		fallTimer = fallTimerMax;
		if (fallPuyo[1] != NOPUYO) { // 子の判定
			if (field[fallY1 - 1][fallX1].puyo != NOPUYO) {
				field[fallY1][fallX1].puyo = fallPuyo[1];
				fallPuyo[1] = NOPUYO;
			}
		}
		// 親の判定
		if (field[fallY - 1][fallX].puyo != NOPUYO) {
			field[fallY][fallX].puyo = fallPuyo[0];
			if (fallPuyo[1] != NOPUYO) { // 子が残っている
				if (field[fallY1 - 1][fallX1].puyo != NOPUYO) {
					field[fallY1][fallX1].puyo = fallPuyo[1];
					CreateFallPuyo();
				} else {
					fallPuyo[0] = fallPuyo[1];
					fallPuyo[1] = NOPUYO;
					fallX = fallX1;
					fallY = fallY1 - 1;
				}
			} else {
				CreateFallPuyo();
			}
		} else {
			fallY -= 1;
		}
		if (fallPuyo[1] == NOPUYO) {
			fallTimer = 0.001f;
		}
	}
	if (fallPuyo[1] != NOPUYO) {
		if (CheckHitKey(KEY_INPUT_M)) {
			if (prevKey == false) {
				rotate = (rotate + 1) % 4;
				int fallX1 = cosf(rotate * DX_PI_F / 2);
				int fallY1 = sinf(rotate * DX_PI_F / 2);
				fallX1 = fallX + fallX1;
				fallY1 = fallY - fallY1;
				if (field[fallY1][fallX1].puyo != NOPUYO) {
					// 子が引っかかるので対策する
					if (fallX1 == fallX + 1) {
						if (field[fallY][fallX - 1].puyo == NOPUYO) {
							fallX -= 1;
						} else {
							rotate = (rotate + 1) % 4;
							fallY += 1;
						}
					} else if (fallX1 == fallX - 1) {
						if (field[fallY][fallX + 1].puyo == NOPUYO) {
							fallX += 1;
						} else {
							rotate = (rotate + 1) % 4;
							fallY -= 1;
						}
					}


				}
			}
			prevKey = true;
		} else {
			prevKey = false;
		}
	}
}

void Field::Draw()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int c = field[y][x].puyo;
			DrawPuyo(x*32, (HEIGHT-y)*32, c);
		}
	}

	DrawPuyo(fallX * 32, (HEIGHT - fallY) * 32, fallPuyo[0]);
	if (fallPuyo[1] != NOPUYO) {
		int addX = cos(rotate * DX_PI_F / 2) * 32;
		int addY = sin(rotate * DX_PI_F / 2) * 32;
		DrawPuyo(fallX * 32 + addX, (HEIGHT - fallY) * 32 + addY, fallPuyo[1]);
	}
}

void Field::DrawPuyo(int x, int y, int puyo)
{
	if (puyo == NOPUYO)
		return;
	int c;
	if (puyo == WALL)
	{
		c = 5;
	}
	else
	{
		c = puyo-1;
	}
	DrawRectGraph(x, y, c * 32, 0, 32, 32, hImage, TRUE);
}

void Field::CreateFallPuyo()
{
	fallPuyo[0] = rand() % 5 + 1;
	fallPuyo[1] = rand() % 5 + 1;
	fallX = 4;
	fallY = 12;
	fallTimer = fallTimerMax;
}

bool Field::KeyRepeat(bool pushKey, int& counter)
{
	static const int FIRST = 30;
	static const int INTERVAL = 5;
	if (pushKey) {
		int c = counter;
		counter++;
		if (c == 0 || (c>= FIRST) && (c- FIRST)% INTERVAL ==0)
			return true;
	} else {
		counter = 0;
	}
	return false;
}
