#include "GameOver.h"

GameOver::GameOver()
{
	hImage = LoadGraph("data/image/font.png");
	position.x = 400;
	position.y = -64;
	startY = -64;
	goalY = 400;
	frame = 0;
}

GameOver::~GameOver()
{
}

//0Å`1ÇÃìÆÇ´ï˚ÇïœâªÇ≥ÇπÇÈ
float ease(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

void GameOver::Update()
{
	int MaxTime = 60;
	frame += 1;
	if (frame > MaxTime)
		frame = MaxTime;
	float time = (float)frame / MaxTime;
	float rate = ease(time);

	float range = (goalY - startY);
	position.y = range * rate + startY;
}

void GameOver::Draw()
{
	DrawRectGraph(position.x, position.y,
				0, 128, 256, 64, hImage, TRUE);
	DrawRectGraph(position.x+256, position.y,
				0, 192, 256, 64, hImage, TRUE);
	DrawRectGraph(position.x, 400,
				0, 128, 256, 64, hImage, TRUE);
}
