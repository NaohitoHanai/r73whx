#include "Boid.h"

Boid::Boid(int x, int y)
{
	position = VECTOR2(x, y);
}

Boid::~Boid()
{
}

void Boid::Update()
{
}

void Boid::Draw()
{
	unsigned int col = GetColor(255,0,0);
	DrawCircle(position.x, position.y, 5, col, 1);
}
