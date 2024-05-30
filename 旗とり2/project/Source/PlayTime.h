#pragma once
#include "../Library/gameObject.h"

class PlayTime : public GameObject {
public:
	PlayTime();
	~PlayTime();
	void Update() override;
	void Draw() override;
private:
	int second;//5‚©‚ç‚¾‚ñ‚¾‚ñ‰º‚ª‚é
};