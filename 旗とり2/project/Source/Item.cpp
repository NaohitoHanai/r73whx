#include "Item.h"

Item::Item()
{
    hImage = LoadGraph("data/image/target.png");
    position.x = 600;
    position.y = 500;
}

Item::~Item()
{
}

void Item::Update()
{
}

void Item::Draw()
{
    DrawRectGraph(position.x, position.y,
        0, 0, 64, 64, hImage, TRUE);
}

VECTOR Item::GetPosition()
{
    return position;
}
