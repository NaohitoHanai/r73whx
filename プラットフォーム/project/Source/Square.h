#pragma once
#include "../Library/gameObject.h"

class Square : public GameObject {
public:
	Square();
	~Square();
	void Update() override;
	void Draw() override;
	void SetPosition(VECTOR pos);
private:
	VECTOR position;
	float rot;
	float scale;
	VECTOR p1;
	VECTOR p2;
	VECTOR p3;
	VECTOR p4;
};