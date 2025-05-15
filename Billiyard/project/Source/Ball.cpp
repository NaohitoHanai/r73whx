#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR pos)
{
	number = num;
	position = pos;
	hImage = LoadGraph("data/textures/billiyard.png");

	power = 20.0f;
	angle = 0.0f;
	velocity = VGet(0,0,0);
	addVec = VGet(0,0,0);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (number == 0) {
		Control(); // 0�̋ʂ�������ł���
	}
	position += velocity;
	// �ǂŒ��˕Ԃ�
	// ��ʂ̃T�C�Y��Screen::WIDTH��Screen::HEIGHT�Œ�`����Ă���
	// �{�[���̑傫���́A���a44
	if (position.x - 44 <= 0) { // ���ɓ�������
		velocity.x *= -1.0f;
		float in = position.x-44; // �߂荞�񂾗ʁi�������}�C�i�X 
		position.x -= in;
		position.x = 44;
	}
	if (position.x + 44 >= Screen::WIDTH) { // �E�ɓ�������
		velocity.x *= -1.0f;
		float in = position.x+44 - Screen::WIDTH; // �߂荞��ł���
		position.x -= in;
	}
	if (position.y - 44 <= 0) { // ��ɓ�������
		velocity.y *= -1.0f;
		float in = position.y - 44; // �߂荞�񂾗ʁi�������}�C�i�X 
		position.y -= in;
	}
	if (position.y + 44 >= Screen::HEIGHT) { // ���ɓ�������
		velocity.y *= -1.0f;
		float in = position.y + 44 - Screen::HEIGHT; // �߂荞��ł���
		position.y -= in;
	}

	// ���C�Ō�������
	float len = VSize(velocity); // ����
	len -= 0.01f; // ���C
	if (len <= 0.0f) {
		velocity = VGet(0, 0, 0);
	} else {
		velocity = VNorm(velocity) * len;
	}
}

void Ball::Draw()
{
	int num = number - 1;
	if (num < 0)
		num = 15;
	int x = (num % 4) * 96;
	int y = (num / 4) * 96;
	DrawRectGraph(position.x-48, position.y-48, //position�͋ʂ̒��S���W
		x, y, 96, 96, hImage, true);
	if (number == 0) {
		VECTOR pos2 = VGet(-100, 0, 0) * MGetRotZ(angle) + position;
		// ���@�@�@�@�����������Ă��邩�������Ă�������
		DrawLine(position.x, position.y, 
			pos2.x, pos2.y, GetColor(255,0,0));
	}
}

void Ball::ResetVec()
{
	addVec = VGet(0,0,0);
}

void Ball::HitBall(Ball* b)
{
	VECTOR diff = b->position - position;
	if (VSize(diff) < 44 + 44) {//�������Ă���
		VECTOR dir = VNorm(diff); // �͂�n�������x�N�g��(�����P)
		// ��������
		float overlapValue = 44+44- VSize(diff);
		position -= dir * (overlapValue/2.0f);// dir�̋t�����ɁAoverlapValue�̔���
		b->position += dir * (overlapValue/2.0f);// dir�̌����ɁAoverlapValue�̔���
		// ����ɗ͂�n��
		float addPower = VDot(velocity, dir); // �n���x�N�g��
		float getPower = VDot(b->velocity, dir * -1); // ���炤�x�N�g��
		b->addVec += dir * addPower;
		addVec -= dir * addPower;
		addVec -= dir * getPower; // dir�̋t�����Ȃ̂�
		b->addVec += dir * getPower;
	}
}

void Ball::AddVec()
{
	velocity += addVec;
}

void Ball::Control()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		angle += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		angle -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		// �˂�
		velocity = VGet(1,0,0) * MGetRotZ(angle) * power;
	}
}
