#pragma once
//Map.h
#include "../Library/gameObject.h"
#include "../Library/csvReader.h"
class Map : public GameObject {
public:
	Map();
	~Map();
	void Start() override; // �ŏ���Update���Ă΂��O
	void Draw() override;

	/// <summary>
	/// �E����i��ł������̓����蔻��
	/// </summary>
	/// <param name="pos">���肷����W</param>
	/// <returns>�߂荞��ł��</returns>
	int HitCheckRight(VECTOR pos);

	int HitCheckLeft(VECTOR pos);

	int HitCheckDown(VECTOR pos);

	int HitCheckUp(VECTOR pos);

private:
	int hImage;
	CsvReader* csv;
};