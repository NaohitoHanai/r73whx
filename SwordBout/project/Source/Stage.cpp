#include "Stage.h"
#include <fstream>
#include <vector>
#include "Goblin.h"
#include "StageObj.h"

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
			float y = stof(strs[3]);
			float z = stof(strs[4]);
			float rx = stof(strs[5]);
			float ry = stof(strs[6]);
			float rz = stof(strs[7]);
			float sx = stof(strs[8]);
			float sy = stof(strs[9]);
			float sz = stof(strs[10]);
			new StageObj(kind, VGet(x,y,z), VGet(rx,ry,rz), VGet(sx,sy,sz));
		}
	}
	csv.close();
}

Stage::~Stage()
{
}

void Stage::Draw()
{
}
