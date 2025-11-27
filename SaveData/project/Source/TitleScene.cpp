#include "TitleScene.h"
#include <fstream>
#include "SaveLoad.h"

TitleScene::TitleScene()
{
	Player p;
	p.level = 10;
	p.position = VECTOR3(0.5, 0.3, 0.1);
	p.hp = 30;

	std::list<Enemy> enemies;
	for (int i = 0; i < 3; i++) {
		Enemy e;
		e.hp = rand();
		e.position = VECTOR3(0, 0, 0);
		enemies.push_back(e);
	}

	std::list<Item> items;
	for (int i = 0; i < 4; i++) {
		Item it;
		it.position = VECTOR3(1, 1, 1);
		items.push_back(it);
	}

	std::ofstream ofs("save.dat", std::ios::binary); // ファイルを開く
	// ToDo:ヘッダーを作って保存
	Header header;
	for (int i=0; i<4; i++)
		header.id[i] = MY_ID[i];
	header.playerNum = 1;
	header.enemyNum = enemies.size();
	header.itemNum = items.size();
	header.fileSize = sizeof(Header)+sizeof(Player)*header.playerNum+
			sizeof(Enemy)*header.enemyNum + sizeof(Item)*header.itemNum+4;
	header.checkSum = 0;
	ofs.write((char*)&header, sizeof(header)); // Headerの保存

	{ //Playerのチェックサム
		char* x = (char*)&p;
		for (int i = 0; i < sizeof(p); i++) {
			header.checkSum += *x;
			x++;
		}
	}
	ofs.write((char*)&p, sizeof(p)); // Playerの保存
	// ToDo:Enemyを保存
	for (Enemy& e : enemies) {
		ofs.write((char*)&e, sizeof(e));
	}
	// ToDo:Itemを保存
	for (Item& i : items) {
		ofs.write((char*)&i, sizeof(i));
	}
	ofs.write("END", 4); // 終わりマーク
	ofs.close(); // ファイルを閉じる
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
	DebugPrintf("%f\n", Time::DeltaTime());
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime());
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
