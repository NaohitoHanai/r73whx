#pragma once
#include "RedGoblin.h"

class RedGoblinAI
{
public:
	RedGoblinAI(RedGoblin* p) { parent = p; }
	~RedGoblinAI();
	void Update();
private:
	RedGoblin* parent;
	int attackPhase; // UŒ‚‚Ì—¬‚ê
};