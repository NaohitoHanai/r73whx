#include "Score.h"
#include "DataCarrier.h"

Score::Score()
{
	score = 0;
//	DataCarrier* d = DataCarrier::GetInstance();
//	d->HighScore = 0;

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
	// scoreがhighScoreより大きければ
	// highScoreを更新
	DataCarrier* d = DataCarrier::GetInstance();
	if (score > d->HighScore) {
		d->HighScore = score;
	}
}
