#pragma once
#include "../Library/gameObject.h"

class Item : public GameObject {
public:
	Item();
	~Item();
	void Update() override;
	void Draw() override;
	VECTOR GetPosition() {
		return position;
	}
private:
	int hImage;
	VECTOR position;

	bool taken;
};