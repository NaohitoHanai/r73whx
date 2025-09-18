#include "BoidManager.h"
#include "Boid.h"
#include <thread>

static const int THREADS = 8;
std::thread thread[THREADS];
std::list<Boid*> boidThread[THREADS];

void func(int idx)
{
	for (Boid* b : boidThread[idx])
	{
		b->Update();
	}
}

BoidManager::BoidManager()
{
	boids.clear();
}

BoidManager::~BoidManager()
{
	boids.clear();
}

void BoidManager::Update()
{
	// positions‚ðì‚é
	positions.clear();
	for (Boid* b : boids)
	{
		positions.push_back(b->GetPosition());
	}
	// boids‚ðboidThread‚É•ª‚¯‚é
	int t = 0;
	for (int t = 0; t < THREADS; t++) {
		boidThread[t].clear();
	}
	for (Boid* b : boids)
	{
		boidThread[t].push_back(b);
		t = (t + 1) % THREADS;
	}

	for (int t = 0; t < THREADS; t++) {
		thread[t] = std::thread(func, t);
	}
	for (int t = 0; t < THREADS; t++) {
		thread[t].join();
	}
}

void BoidManager::Draw()
{
	for (Boid* b : boids) {
		b->Draw();
	}
}

void BoidManager::Add(Boid* b)
{
	boids.push_back(b);
}
