#include "TitleScene.h"
#include <thread>

void func()
{
	for (int i = 0; i < 1000; i++)
	{
		char buf[256];
		sprintf_s<256>(buf, "I=%d\n", i);
		OutputDebugString(buf);
		for (int j = 0; j < 100; j++)
		{
		}
	}
}

TitleScene::TitleScene()
{
	std::thread th1(func);
	std::thread th2(func);
	th1.join();
	th2.join();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime());
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
