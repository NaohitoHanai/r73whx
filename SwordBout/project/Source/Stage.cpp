#include "Stage.h"
#include <fstream>
#include <vector>
#include "Goblin.h"
#include "RedGoblin.h"
#include "StageObj.h"
#include "Field.h"

using namespace std;

vector<string> split(string s) {
	vector<string> ret;

	for (int index = 0; index < s.length(); index++) {
		if (s[index] == ',') {
			string s1 = s.substr(0, index);
			s = s.substr(index+1);
			index = 0;
			ret.push_back(s1);
		}
	}
	ret.push_back(s);
	return ret;
}

Stage::Stage()
{
	ifstream csv("data/stage00.csv");
	string str;
	while (!csv.eof()) { // eofはファイルの終わりでtrueになる
		getline(csv, str); // １行読む
		vector<string> strs = split(str);
		if (strs[0] == "CHARA") {
			float x = stof(strs[2]);
			float y = stof(strs[3]);
			float z = stof(strs[4]);
			float ry = stof(strs[6]);
			new Goblin(VGet(x, y, z), ry);
		} else if (strs[0] == "OBJ") {
			int kind = stoi(strs[1]);
			float x = stof(strs[2]);
			float sy = stof(strs[9]);
			float sz = stof(strs[10]);
//			new StageObj(kind, VGet(x,y,z), VGet(rx,ry,rz), VGet(sx,sy,sz));
		}
	}
	csv.close();
	new RedGoblin(VGet(0, 150, 500), 0);
}

Stage::~Stage()
{
}

void Stage::Draw()
{
}

bool Stage::SearchObject(VECTOR pos1, VECTOR pos2, VECTOR* hit)
{
	bool ret = false;
	std::list<StageObj*> objs = FindGameObjects<StageObj>();
#if false
	// イテレーターで回す方
	for (std::list<StageObj*>::iterator itr = objs.begin();
										itr != objs.end(); itr++) {
		(*itr)->SearchObject(pos1, pos2, hit);
	}
#endif
	// 範囲forで回す方
	float nearestDist = VSize(pos1-pos2); // 一番近い距離
	VECTOR nearest; // 結果
	VECTOR tmp;
	Field* f = FindGameObject<Field>();
	if (f->SearchGround(pos1, pos2, &tmp)) { // 当たった
		float nowDist = VSize(tmp - pos1);
		if (nowDist < nearestDist) {
			nearestDist = nowDist;
			nearest = tmp;
			ret = true;
		}
	}
	for (StageObj* obj : objs) {
		if (obj->SearchObject(pos1, pos2, &tmp)) { // 当たった
			float nowDist = VSize(tmp-pos1);
			if (nowDist < nearestDist) {
				nearestDist = nowDist;
				nearest = tmp;
				ret = true;
			}
		}
	}
	if (hit != nullptr) {
		*hit = nearest;
	}
	return ret;
}
