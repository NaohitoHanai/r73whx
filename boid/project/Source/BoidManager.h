#pragma once
#include "../Library/GameObject.h"

class Boid;
class BoidManager : public GameObject {
public:
	BoidManager();
	~BoidManager();
	void Add(Boid* b);
	const std::list<Boid*>& All() { return boids; }
private:
	std::list<Boid*> boids;
};