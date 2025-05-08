#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR pos)
{
	number = num;
	position = pos;
	hImage = LoadGraph("data/textures/billiyard.png");

	power = 5.0f;
	angle = 0.0f;
	velocity = VGet(0,0,0);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (number == 0) {
		Control(); // 0の玉だけ操作できる
	}
	position += velocity;
	// 壁で跳ね返る
	// 画面のサイズはScreen::WIDTHとScreen::HEIGHTで定義されている
	// ボールの大きさは、半径44
	if (position.x - 44 <= 0) { // 左に当たった
		velocity.x *= -1.0f;
		float in = position.x-44; // めり込んだ量（ただしマイナス 
		position.x -= in;
	}
	if (position.x + 44 >= Screen::WIDTH) { // 右に当たった
		velocity.x *= -1.0f;
		float in = position.x+44 - Screen::WIDTH; // めり込んでいる
		position.x -= in;
	}
	if (position.y - 44 <= 0) { // 上に当たった
		velocity.y *= -1.0f;
		float in = position.y - 44; // めり込んだ量（ただしマイナス 
		position.y -= in;
	}
	if (position.y + 44 >= Screen::HEIGHT) { // 下に当たった
		velocity.y *= -1.0f;
		float in = position.y + 44 - Screen::HEIGHT; // めり込んでいる
		position.y -= in;
	}

	// 摩擦で減速する
	float len = VSize(velocity); // 長さ
	len -= 0.01f; // 摩擦
	if (len <= 0.0f) {
		velocity = VGet(0, 0, 0);
	} else {
		velocity = VNorm(velocity) * len;
	}

	// 他の玉と当てる
	std::list<Ball*> balls = FindGameObjects<Ball>();
	for (Ball* b : balls) {
		if (b == this)
			continue;
		if (VSize(b->position - position) < 44 + 44) {
			VECTOR dir = b->position - position;
			dir = VNorm(dir); // 力を渡す向きベクトル
			float addPower = VDot(velocity, dir);
			VECTOR addVec = dir * addPower;
			b->velocity += addVec;
			velocity -= addVec;
		}
	}
}

void Ball::Draw()
{
	int num = number - 1;
	if (num < 0)
		num = 15;
	int x = (num % 4) * 96;
	int y = (num / 4) * 96;
	DrawRectGraph(position.x-48, position.y-48, //positionは玉の中心座標
		x, y, 96, 96, hImage, true);
	if (number == 0) {
		VECTOR pos2 = VGet(-100, 0, 0) * MGetRotZ(angle) + position;
		// 問題　　　　↑が何をしているか説明してください
		DrawLine(position.x, position.y, 
			pos2.x, pos2.y, GetColor(255,0,0));
	}
}

void Ball::Control()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		angle += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		angle -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		// 突く
		velocity = VGet(1,0,0) * MGetRotZ(angle) * power;
	}
}
