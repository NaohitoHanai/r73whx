#pragma once
//ResultScene.h
#include "../Library/sceneBase.h"

class ResultScene : public SceneBase {
public:
	ResultScene();
	~ResultScene();
	void Update() override;
	void Draw() override;
private:
	int frame;
};
