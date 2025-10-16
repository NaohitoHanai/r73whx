#include "TitleScene.h"
#include "HashTable.h"

TitleScene::TitleScene()
{
	HashTable* hash = new HashTable();
	hash->Set("Attack", 20);
	hash->Set("MaxLife", 1000);
	hash->Set("Atatck", 100);
	hash->Set("Attack", 30);

	int a = hash->Get("Attack");
	char s[20];
	sprintf_s<20>(s, "a=%d\n", a);
	OutputDebugString(s);
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
