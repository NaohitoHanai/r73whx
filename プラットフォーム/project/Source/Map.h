#pragma once
//Map.h
#include "../Library/gameObject.h"

class Map : public GameObject {
public:
	Map();
	~Map();
	void Draw() override;

	/// <summary>
	/// ‰E‚©‚çi‚ñ‚Å‚«‚½‚Ì“–‚½‚è”»’è
	/// </summary>
	/// <param name="pos">”»’è‚·‚éÀ•W</param>
	/// <returns>‚ß‚è‚ñ‚Å‚é—Ê</returns>
	int HitCheckRight(VECTOR pos);

	int HitCheckLeft(VECTOR pos);

private:
	int hImage;
};