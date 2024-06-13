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

void GameOver::Update()
{
	frame += 1;
	if (frame > 30)
		frame = 30;
	float time = frame / 30.0f;
	float rate = time;
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
