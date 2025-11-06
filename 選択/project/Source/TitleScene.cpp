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

// 自由線選択用の点の配列
struct VECTOR2 {
	float x, y;
	VECTOR2(float _x, float _y) { x = _x; y = _y; }
};
std::vector<VECTOR2> pivots;
bool selecting; // 選択中

TitleScene::TitleScene()
{
	selecting = false;

	points.resize(1); // 配列のサイズを決める
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
	//if (GetMouseInput() & MOUSE_INPUT_LEFT) { // 左ボタンを押してる
	//	int x, y;
	//	GetMousePoint(&x, &y);
	//	box.left = x;
	//	box.top = y;
	//}

	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
		if (selecting) {
			int x, y;
			GetMousePoint(&x, &y);
			VECTOR2 prev = *(pivots.rbegin()); // 最後の点
			float xd = prev.x - x;
			float yd = prev.y - y;
			if (xd * xd + yd * yd >= 20 * 20) {
				pivots.push_back(VECTOR2(x, y));
			}
		} else {
			pivots.clear(); // 最初の１点
			int x, y;
			GetMousePoint(&x, &y);
			pivots.push_back(VECTOR2(x, y));
			selecting = true;
		}
	} else {
		if (selecting) {
			// 点を閉じる
			pivots.push_back(pivots[0]);
			// 範囲内を選択状態にする
			for (auto& p : points) { //全部の点
				bool inside = false;
				for (int i = 1; i < pivots.size(); i++) {
					VECTOR2 pv1 = pivots[i-1];
					VECTOR2 pv2 = pivots[i];
					VECTOR2 pt1 = VECTOR2(p.pos.x, p.pos.y);					
					VECTOR2 pt2 = VECTOR2(-1, -1);
					// pv1-pv2とpt1-pt2が交差していれば
					// inside = !inside;
				}
				p.selected = inside;
			}
			selecting = false;
		}
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

	for (int i = 1; i < pivots.size(); i++) {
		DrawLine(pivots[i-1].x, pivots[i-1].y,
			pivots[i].x, pivots[i].y, GetColor(128,128,128));
	}
	for (auto& p : points) {
		DrawCircle(p.pos.x, p.pos.y, 2, Cols[p.color], TRUE);
	}
	for (auto& p : points) {
		if (p.selected) {
			DrawCircle(p.pos.x, p.pos.y, 3,
							GetColor(255,255,255), FALSE);
		}
	}

	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}


