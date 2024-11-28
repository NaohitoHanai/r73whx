#pragma once
// Animator.h
#include <string>

class Animator {
public:
	Animator(int m);
	~Animator();
	void Update();
	void Play(std::string filename, bool loop);
	bool IsFinish();
	float CurrentAnimTime() {
		return animTime;
	}
private:
	int model;
	int handle;
	int attachID;
	float animTime;
	int animMaxTime;
	std::string currentFile;
	bool loopMode;
};