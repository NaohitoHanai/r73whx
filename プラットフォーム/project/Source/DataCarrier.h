#pragma once
// DataCarrier

// �V���O���g���ō��
// �V���O���g���́A�C���X�^���X���P�����K�����݂���N���X
class DataCarrier {
public:
	static DataCarrier* GetInstance() { // static�̊֐�
		static DataCarrier* instance = nullptr; // �C���X�^���X��static
		if (instance == nullptr) {
			instance = new DataCarrier();
		}
		return instance;
	}
	int HighScore;
private:
	DataCarrier() { // �R���X�g���N�^�[��private
		HighScore = 0;
	}
};