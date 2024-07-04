#include "Item.h"
#include <assert.h>
#include "Player.h"
#include "config.h"
#include "Score.h"

Item::Item()
{
	hImage = LoadGraph("data/image/target.png");
	assert(hImage > 0);

	position.x = rand() % (SCREEN_WIDTH - 64);
	position.y = rand() % (SCREEN_HEIGHT - 64);

	taken = false;
}

Item::~Item()
{
	DeleteGraph(hImage);
}

void Item::Update()
{
	if (taken == false) {
		Player* pPlayer = FindGameObject<Player>();
		VECTOR pPos = pPlayer->GetPosition();
		VECTOR dif = pPos - position;
		if (VSize(dif) < 64 + 64) {
			taken = true; // ��������Ƃɂ���
		}
	}
	else {
		Player* pPlayer = FindGameObject<Player>();
		VECTOR pPos = pPlayer->GetPosition();
		VECTOR v = pPos - position;
		// v�̒�����5�ɂ��遨v�̒�����1�ɂ��Ă���5�{����
		v = VNorm(v) * 5.0f;
		position += v; // ���x5.0�Ńv���C���[�ɋ߂Â�

		VECTOR dif = pPos - position;
		// C++�̗����́Arand()���ď����ƁA�������擾�ł��܂��B
		// 0�`32767�̂����ꂩ���ς���
		// 32767�́ARAND_MAX�Ə����Ă�����
		if (VSize(dif) < 5) {
			position.x = rand() % (SCREEN_WIDTH-64);
			position.y = rand() % (SCREEN_HEIGHT-64);
			taken = false;
			Score* sc = FindGameObject<Score>();
			sc->Add(100);
		}
	}
}

void Item::Draw()
{
	Player* pPlayer = FindGameObject<Player>();
	VECTOR p = position - pPlayer->GetCameraPosition();
	DrawRectGraph(p.x, p.y, 0, 0, 64, 64, hImage, TRUE);
}

void Item::SetPosition(int x, int y)
{
	position = VGet(x, y, 0);
}
