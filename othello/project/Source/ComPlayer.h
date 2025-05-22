#pragma once
#include "Player.h"

class ComPlayer : public Player
{
public:
	ComPlayer(Board::CELL_STATE color);
	~ComPlayer();
	void Update() override;
	void Draw() override;
private:
	float waitTimer;
	int evalPoint[8][8]; // •]‰¿“_
};