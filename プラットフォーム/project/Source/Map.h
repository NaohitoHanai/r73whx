#pragma once
//Map.h
#include "../Library/gameObject.h"
#include "../Library/csvReader.h"
class Map : public GameObject {
public:
	Map();
	~Map();
	void Start() override; // 最初にUpdateが呼ばれる前
	void Draw() override;

	/// <summary>
	/// 右から進んできた時の当たり判定
	/// </summary>
	/// <param name="pos">判定する座標</param>
	/// <returns>めり込んでる量</returns>
	int HitCheckRight(VECTOR pos);

	int HitCheckLeft(VECTOR pos);

	int HitCheckDown(VECTOR pos);

	int HitCheckUp(VECTOR pos);

private:
	int hImage;
	CsvReader* csv;
};