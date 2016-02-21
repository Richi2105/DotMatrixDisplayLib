#include "DisplayPosition.h"
#include <OS_DEF.h>

DisplayPosition::DisplayPosition(int x, int y)
{
    this->xPosition = x;
    this->yPosition = y;
}

DisplayPosition::DisplayPosition()
{
    this->xPosition = 0;
    this->yPosition = 0;
}

DisplayPosition::~DisplayPosition()
{
    //dtor
}

int DisplayPosition::getXPosition()
{
    return this->xPosition;
}

int DisplayPosition::getYPosition()
{
    return this->yPosition;
}

void DisplayPosition::setXPosition(int xpos)
{
	this->xPosition = xpos;
}
void DisplayPosition::setYPosition(int ypos)
{
	this->yPosition = ypos;
}

int DisplayPosition::getSerializedSize()
{
	int16_t size = 0;
	size += sizeof(this->xPosition);
	size += sizeof(this->yPosition);

	return size;
}
int DisplayPosition::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	packData(data2, this->xPosition);
	packData(data2, this->yPosition);

	return this->getSerializedSize();
}
int DisplayPosition::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackData(data2, this->xPosition);
	unpackData(data2, this->yPosition);

	return this->getSerializedSize();
}
