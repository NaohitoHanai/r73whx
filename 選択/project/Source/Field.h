#pragma once
#include "../Library/GameObject.h"

class Field : public GameObject {
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

	bool IsWallBlock(VECTOR pos);
private:
	int hModel;
	// struct VECTOR {
	//  float x, y, z;
	// };
	VECTOR rotation;
};