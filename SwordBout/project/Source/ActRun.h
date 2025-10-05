#pragma once
//ActRun.h
 #include "ActionBase.h"

class ActRun : public ActionBase
{
public:
	ActRun(Object3D* base);
	~ActRun();
	void Update() override;
	void Suspend() override;
	void Resume() override;
};