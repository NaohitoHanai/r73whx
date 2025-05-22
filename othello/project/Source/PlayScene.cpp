#include "PlayScene.h"
#include "Board.h"
#include "Player.h"
#include "ComPlayer.h"

PlayScene::PlayScene()
{
	new Board();
	player[0] = new Player(Board::BLACK);
	player[1] = new ComPlayer(Board::WHITE);
	turn = 0;
	player[turn]->TurnStart();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (player[turn]->TurnEnded()) {
		if (turn==0)
			turn = 1;
		else
			turn = 0;
		player[turn]->TurnStart();
	}
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}




//class A {
//public:
//	A() {}
//	virtual ~A() {}
//	virtual void Update() {}
//};
//
//class B : public A {
//public:
//	B() {}
//	~B() {}
//	void Update() override {}
//};
//
//A* inst = new B(); // �h���N���X��new���Ċ��N���X�Ŏ���
////new B()������ƁA���N���X�̃R���X�g���N�^�A�h���N���X�̃R���X�g���N�^
////�̏��ŌĂ΂�܂�
//
//delete inst; // ���̂ӂ肵�Ă���C���X�^���X���폜
////���N���X�̃f�X�g���N�^���Ă΂��̂ŁA�h���N���X�̃f�X�g���N�^��
//// �Ă΂�Ȃ�
////���N���X�̃f�X�g���N�^��virtual�������Ă���ƁA�h���N���X�̃f�X�g���N�^��
//// �Ă΂��
//
//
//
//
//
//
//
//
//
//
//
//
