#pragma once
#include "../Library/SceneBase.h"
#include "Player.h"

/// <summary>
/// �Q�[���v���C�̃V�[���𐧌䂷��
/// </summary>
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	int turn;
	float dispTime; // ���b�Z�[�W��\�����鎞��
	enum Phase {
		DISP_MESSAGE = 0, // �����̔Ԃł��A�p�X�ł�
		PLAYING, // ���͑҂�
	};
	Phase phase;
	Player* player[2];
};
