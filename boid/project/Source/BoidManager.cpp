#include "BoidManager.h"
#include "Boid.h"
#include <thread>

static const int THREADS = 8;
std::thread thread[THREADS];
std::list<Boid*> boidThread[THREADS];

LARGE_INTEGER freq; //�������Ԍv���p

void func(int idx)
{
	for (Boid* b : boidThread[idx])
	{
		b->Update();
	}
}

BoidManager::BoidManager()
{
	QueryPerformanceFrequency(&freq); // CPU�̎��g��
	boids.clear();
}

BoidManager::~BoidManager()
{
	boids.clear();
}

void BoidManager::Update()
{
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current); // CPU�̏����J�E���^�[

	// positions�����
	positions.clear();
	for (Boid* b : boids)
	{
		positions.push_back(b->GetPosition());
	}
	// boids��boidThread�ɕ�����
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
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end); // CPU�̏����J�E���^�[
	float dt = static_cast<float>(
		end.QuadPart - current.QuadPart) / freq.QuadPart; //�b
	char buf[256];
	sprintf_s<256>(buf, "DT=%f\n", dt);
	OutputDebugString(buf);
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
