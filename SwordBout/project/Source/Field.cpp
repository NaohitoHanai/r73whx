#include "Field.h"
#include <assert.h>
Field::Field()
{
	hModel = MV1LoadModel("data/Stage/Stage00.mv1");
	assert(hModel > 0);
}

Field::~Field()
{
}

void Field::Update()
{
}
