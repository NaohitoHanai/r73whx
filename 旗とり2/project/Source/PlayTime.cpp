#include "PlayTime.h"
#include "GameOver.h"

PlayTime::PlayTime()
{
	second = 5 * 60;
}

PlayTime::~PlayTime()
{
}

void PlayTime::Update()
{
	second -= 1;
	if (second == 0) {
		Instantiate<GameOver>();
	}
}

void PlayTime::Draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255),
		"TIME:%d", second / 60);
}
