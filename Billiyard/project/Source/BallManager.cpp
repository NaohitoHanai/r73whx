#include "BallManager.h"
#include "Ball.h"

void BallManager::Update()
{
	std::list<Ball*> balls = FindGameObjects<Ball>();
	for (Ball* b : balls) {
		b->ResetVec();
	}
	for (auto itr = balls.begin(); itr != balls.end(); itr++) {
		auto itr2 = itr;
		for (itr2++; itr2 != balls.end(); itr2++) {
			Ball* b1 = *itr;
			Ball* b2 = *itr2;
			b1->HitBall(b2);
		}
	}
	for (Ball* b : balls) {
		b->AddVec();
	}
	// ここで、リーグ戦の回し方
	// 4チームのリーグ戦として、
	//int m[4];

	//for (int i = 0; i < 4; i++) {
	//	// 片方の対戦者は、m[i];
	//	for (int j = i + 1; j < 4; j++) { // 自分の次
	//		// もう片方の対戦者はm[j]
	//}
}

//