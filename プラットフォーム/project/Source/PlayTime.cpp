#include "PlayTime.h"
#include "GameOver.h"

PlayTime::PlayTime()
{
	second = 5*60;
}

PlayTime::~PlayTime()
{
}

void PlayTime::Update()
{
	if (second > 0) {
//		--second;
		if (second==0) {
			Instantiate<GameOver>();
		}
	}
}

void PlayTime::Draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255),
		"TIME:%d.%02d", second/60, (second%60)*100/60);
}
