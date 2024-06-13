#include "Score.h"

Score::Score()
{
	score = 0;
}

Score::~Score()
{
}

void Score::Update()
{
}

void Score::Draw()
{
	DrawFormatString(900, 0, GetColor(255, 255, 255), "SCORE: %6d", score);
}

void Score::Add(int val)
{
	score += val;
}
