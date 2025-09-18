#include "Boid.h"
#include "BoidManager.h"

Boid::Boid(int x, int y)
{
	man = FindGameObject<BoidManager>();
	man->Add(this);
	position = VECTOR2(x, y);
}

Boid::~Boid()
{
}

void Boid::Update()
{
	// ①今の移動 velocity
	// ②マウスカーソルに向かう
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	VECTOR2 add2 = VECTOR2(mouseX, mouseY) - position;
	add2 = add2.Normalize() * 0.5f;
	velocity += add2;
	// ③分離 一番近い物を探して、一定距離(10)以下なら離れようとする
	VECTOR2 nearPos;
	float nearDist = 9999999;
	auto& pos = man->AllPosition();
	for (VECTOR2 p : pos) {
		if ((p - position).Size()==0) // 自分を除外
			continue;
		VECTOR2 d = p - position;
		float dsize = d.Size();
		if (dsize < nearDist) {
			nearDist = dsize;
			nearPos = p;
		}
	}
	// 一番近いの(nearBoid)が見つかったので、離れる
	if (nearDist < 10.0f) {
		VECTOR2 add3 = position - nearPos;
		add3 = add3.Normalize() * 0.5f;
		velocity += add3;
	}
	// ④結合
	if (nearDist > 100.0f) {
		VECTOR2 add4 = nearPos - position;
		add4 = add4.Normalize() * 0.5f;
		velocity += add4;
	}

	if (velocity.Size() > 5.0f) {
		velocity = velocity.Normalize() * 5.0f;
	}
	position += velocity;
}

void Boid::Draw()
{
	unsigned int col = GetColor(255,0,0);
	DrawCircle(position.x, position.y, 5, col, 1);
}
