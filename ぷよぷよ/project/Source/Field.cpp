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
					Connect();
					CreateFallPuyo();
				} else {
					fallPuyo[0] = fallPuyo[1];
					fallPuyo[1] = NOPUYO;
					fallX = fallX1;
					fallY = fallY1 - 1;
				}
			} else {
				Connect();
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
			DrawPuyo(x*32, (HEIGHT-y)*32, field[y][x]);
		}
	}

	DrawPuyo(fallX * 32, (HEIGHT - fallY) * 32, fallPuyo[0]);
	if (fallPuyo[1] != NOPUYO) {
		int addX = cos(rotate * DX_PI_F / 2) * 32;
		int addY = sin(rotate * DX_PI_F / 2) * 32;
		DrawPuyo(fallX * 32 + addX, (HEIGHT - fallY) * 32 + addY, fallPuyo[1]);
	}
}

void Field::Connect()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			field[y][x].connect = 0;
			field[y][x].erase = false;
		}
	}
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int c = field[y][x].puyo;
			if (c != WALL && c != NOPUYO) {
				// 上下左右につながっている判定
				if (field[y][x + 1].puyo == c) {
					field[y][x].connect |= CELL::RIGHT;
				}
				if (field[y][x - 1].puyo == c) {
					field[y][x].connect |= CELL::LEFT;
				}
				if (y < HEIGHT - 1 && field[y + 1][x].puyo == c) {
					field[y][x].connect |= CELL::UP;
				}
				if (field[y - 1][x].puyo == c) {
					field[y][x].connect |= CELL::DOWN;
				}
			}
		}
	}
	// ４つ以上並んだ判定
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int c = field[y][x].puyo;
			if (c != WALL && c != NOPUYO) {
				// ToDo:(Func)全部のcheckedをfalseにする
				EraseChecked();
				field[y][x].checked = true;
				// ToDo:(Func)ここから、４方向チェックする
				int con = CheckConnect(x, y, c);
				// ToDo:合計４個並んでたら、eraseをtrue
				if (con >= 4) {
					field[y][x].erase = true;
				}
			}
		}
	}
}

void Field::EraseChecked()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			field[y][x].checked = false;
		}
	}
}

int Field::CheckConnect(int x, int y, int c)
{
	// ４方向チェック
//	field[y][x].checked = true;
	int ret = 1;
	if (field[y][x + 1].puyo == c && field[y][x + 1].checked == false)
	{
		ret += CheckConnect(x + 1, y, c);
	}
	if (field[y][x - 1].puyo == c && field[y][x - 1].checked == false)
	{
		ret += CheckConnect(x - 1, y, c);
	}
	if (field[y - 1][x].puyo == c && field[y - 1][x].checked == false)
	{
		ret += CheckConnect(x, y - 1, c);
	}
	if (y < HEIGHT-1 &&
		field[y + 1][x].puyo == c && field[y + 1][x].checked == false)
	{
		ret += CheckConnect(x, y + 1, c);
	}
	return ret;
}

void Field::DrawPuyo(int x, int y, CELL& cell)
{
	if (cell.puyo == NOPUYO)
		return;
	int c;
	if (cell.puyo == WALL)
	{
		c = 5;
	} else
	{
		c = cell.puyo - 1;
	}
	DrawRectGraph(x, y, c * 32, cell.connect*32, 32, 32, hImage, TRUE);
	if (cell.erase) {
		DrawCircle(x+16, y+16, 8, 255, 1);
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
