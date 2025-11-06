#include "TitleScene.h"
#include "../Library/MyDxLib.h"
#include <vector>
#include "Screen.h"

unsigned int Cols[] = {
	GetColor(255,0,0),
	GetColor(0,255,0),
	GetColor(0,0,255),
};
struct Point { // 点１個のデータ
	VECTOR pos;  // 座標
	int color; // 色
	bool selected; // 選ばれてる
};
std::vector<Point> points; // 点の配列

RECT box;

TitleScene::TitleScene()
{
	points.resize(300); // 配列のサイズを決める
	for (int i = 0; i < points.size(); i++) {
		int x = rand() % Screen::WIDTH; //Cの乱数
		int y = GetRand(Screen::HEIGHT-1); // DxLibの乱数
		points[i].pos.x = x;
		points[i].pos.y = y;
		points[i].color = 0;
		points[i].selected = false;
	}
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT) { // 左ボタンを押してる
		int x, y;
		GetMousePoint(&x, &y);
		box.left = x;
		box.top = y;
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawBox(box.left, box.top, box.right, box.bottom,
			GetColor(128,128,128), FALSE);

	for (auto& p : points) {
		DrawCircle(p.pos.x, p.pos.y, 2, Cols[p.color], TRUE);
	}

	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}


