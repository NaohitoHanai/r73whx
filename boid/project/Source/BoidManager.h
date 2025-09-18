#pragma once
#include "../Library/GameObject.h"
#include <vector>
class Boid;
class BoidManager : public GameObject {
public:
	BoidManager();
	~BoidManager();
	void Update() override;
	void Draw() override;
	void Add(Boid* b);
	const std::list<Boid*>& All() { return boids; }
	const std::vector<VECTOR2>& AllPosition() { return positions; }
private:
	std::list<Boid*> boids;
	std::vector<VECTOR2> positions; // å©ÇÈópÇÃç¿ïW
};