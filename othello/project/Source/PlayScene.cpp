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
//A* inst = new B(); // 派生クラスでnewして基底クラスで持つ
////new B()をすると、基底クラスのコンストラクタ、派生クラスのコンストラクタ
////の順で呼ばれます
//
//delete inst; // 基底のふりしているインスタンスを削除
////基底クラスのデストラクタが呼ばれるので、派生クラスのデストラクタが
//// 呼ばれない
////基底クラスのデストラクタにvirtualを書いていると、派生クラスのデストラクタが
//// 呼ばれる
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
