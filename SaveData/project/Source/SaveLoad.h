#pragma once
#include "../Library/GameObject.h"

struct Player {
	int level;
	VECTOR3 position;
	float hp;
};

struct Enemy {
	VECTOR3 position;
	float hp;
};

struct Item {
	VECTOR3 position;
};

struct Header {
	char id[4];
	int fileSize; // データのサイズ
	int checkSum; // データの総和

	int playerNum;
	int enemyNum;
	int itemNum;
};

const char MY_ID[] = "NAME"; //自分のゲーム名
