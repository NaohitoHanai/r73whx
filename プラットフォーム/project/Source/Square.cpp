#include "Square.h"

Square::Square()
{
	p1 = VGet(-1, -1, 0);
	p2 = VGet( 1, -1, 0);
	p3 = VGet( 1,  1, 0);
	p4 = VGet(-1,  1, 0);

}

Square::~Square()
{
}

void Square::Update()
{
	scale += 0.5f;
	rot += 10.0f;
	position += VGet(5.0f, 0, 0);
}

void Square::Draw()
{
	MATRIX matS = MGetScale(VGet(scale, scale, scale));
	MATRIX mat = MGetRotZ(DegToRad(rot));
	MATRIX mat2 = MGetTranslate(position);
	MATRIX m = matS * mat * mat2;
	VECTOR pp1 = p1 * m;
	VECTOR pp2 = p2 * m;
	VECTOR pp3 = p3 * m;
	VECTOR pp4 = p4 * m;
	DrawLine(pp1.x, pp1.y, pp2.x, pp2.y, GetColor(0, 255, 0));
	DrawLine(pp2.x, pp2.y, pp3.x, pp3.y, GetColor(0, 255, 0));
	DrawLine(pp3.x, pp3.y, pp4.x, pp4.y, GetColor(0, 255, 0));
	DrawLine(pp4.x, pp4.y, pp1.x, pp1.y, GetColor(0, 255, 0));
}

void Square::SetPosition(VECTOR pos)
{
	scale = 0.0f;
	position = pos + VGet(40, 20, 0);
}
