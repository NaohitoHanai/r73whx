#pragma once
// DataCarrier

// シングルトンで作る
// シングルトンは、インスタンスが１つだけ必ず存在するクラス
class DataCarrier {
public:
	static DataCarrier* GetInstance() { // staticの関数
		static DataCarrier* instance = nullptr; // インスタンスもstatic
		if (instance == nullptr) {
			instance = new DataCarrier();
		}
		return instance;
	}
	int HighScore;
private:
	DataCarrier() { // コンストラクターがprivate
		HighScore = 0;
	}
};