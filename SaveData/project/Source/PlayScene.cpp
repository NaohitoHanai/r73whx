#include "PlayScene.h"
#include <fstream>
#include "SaveLoad.h"

Player p;
std::list<Enemy> enemies;
std::list<Item> items;
PlayScene::PlayScene()
{
	std::ifstream ifs("save.dat", std::ios::binary);
	//Headerを読む
	Header header;
	ifs.read((char*)&header, sizeof(header));
	//エラーチェック
	//header.idがMY_IDと一緒か
	auto pos = ifs.tellg(); // ファイルのどこを読んでいるか
	ifs.seekg(0, std::ios_base::end); // ファイルの最後から０バイト目に移動
	auto size = ifs.tellg(); // これがファイルサイズになる
	ifs.seekg(pos, std::ios_base::beg); // ファイルの位置を元に戻す
	// header.filesizeがsizeと一緒か
	// header.checkSumが一緒か(一旦０と比べる）
	// エラーしてたら読まない

	//Playerを読む
	for (int i = 0; i < header.playerNum; i++) {
		ifs.read((char*)&p, sizeof(p));
	}
	//Enemyを読む
	enemies.clear();
	for (int i = 0; i < header.enemyNum; i++) {
		Enemy e;
		ifs.read((char*)&e, sizeof(e));
		enemies.push_back(e);
	}
	//Itemを読む
	items.clear();
	for (int i = 0; i < header.itemNum; i++) {
		Item it;
		ifs.read((char*)&it, sizeof(it));
		items.push_back(it);
	}
	char s[4];
	ifs.read(s, 4); // ENDマーク
	ifs.close();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), "LEVEL=%d", p.level);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "POS-X=%f", p.position.x);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "HP   =%f", p.hp);

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
