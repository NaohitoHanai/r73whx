#pragma once
//Map.h
#include "../Library/gameObject.h"

class Map : public GameObject {
public:
	Map();
	~Map();
	void Draw() override;
private:
	int hImage;
};