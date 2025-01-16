#include "TitleScene.h"
#include <DxLib.h>
#include <fstream>
using namespace std;

TitleScene::TitleScene()
{
#if false
	ofstream f("data/test.txt"); // �t�@�C�����J��
//	const char* str = "1Aa_";
//	f.write(str, 4); // �t�@�C���ɏ���
//	f.write(str, 4); // �t�@�C���ɏ���
	const int val = 1234;
	f.write((char*)&val, 4);
	f.close(); // �t�@�C�������
#endif
#if false
	ifstream f("data/test.txt");
	f.read((char*)&readVal, 4);
	f.close();
#endif
	ifstream f("data/stage00.csv");
	string str;
	getline(f, str);
	getline(f, str);
	f.close();
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
	DrawFormatString( 100, 100, GetColor(255,255,255),
		"%d", readVal);

	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
