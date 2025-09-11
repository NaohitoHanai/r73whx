#include "BoidManager.h"
#include "Boid.h"

BoidManager::BoidManager()
{
	boids.clear();
}

BoidManager::~BoidManager()
{
	boids.clear();
}

void BoidManager::Add(Boid* b)
{
	boids.push_back(b);
}
