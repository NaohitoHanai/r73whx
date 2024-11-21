#pragma once
// Animator.h
#include <string>

class Animator {
public:
	Animator(int m);
	~Animator();
	void Update();
	void Play(std::string filename);
private:
	int model;
	int handle;
	int attachID;
	float animTime;
	int animMaxTime;
	std::string currentFile;
};