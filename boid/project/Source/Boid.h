#pragma once
#include "../Library/GameObject.h"

class BoidManager;
class Boid {
public:
	Boid(int x, int y);
	~Boid();
	void Update();
	void Draw();
	const VECTOR2& GetPosition() { return position; }
	const VECTOR2& GetVelocity() { return velocity; }
private:
	VECTOR2 position;
	VECTOR2 velocity;
	BoidManager* man;
};
