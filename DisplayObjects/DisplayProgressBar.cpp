/*
 * DisplayProgressBar.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: richard
 */

#include "../DisplayObjects/DisplayProgressBar.h"

#include <stdio.h>

namespace DotMatrix {

DisplayProgressBar::DisplayProgressBar(DisplayPosition pos, int length, int height)
	: boundary(pos.getXPosition(), pos.getYPosition(), pos.getXPosition() + length, pos.getYPosition() + height) {
	this->progress = 0;
}

DisplayProgressBar::DisplayProgressBar(DisplayBoundary boundary) {
	this->boundary = boundary;
	this->progress = 0;
}

DisplayProgressBar::DisplayProgressBar() : boundary()
{
	this->progress = 0;
}

DisplayProgressBar::~DisplayProgressBar() {
	// TODO Auto-generated destructor stub
}

void DisplayProgressBar::setProgressPercent(float percent)
{
	this->progress = (int) (255.0 * percent);
}

int DisplayProgressBar::getProgressPointerPosition()
{
	int xSize = this->boundary.getXPosEnd() - this->boundary.getXPosBegin();
	float prg = (float)this->progress / 255.0;
	return int(float(xSize) * prg);
}

void DisplayProgressBar::display()
{
	if (Displayable::dispCom != nullptr)
		Displayable::dispCom->display(this);
}

DisplayBoundary* DisplayProgressBar::getBoundary()
{
	return &this->boundary;
}

int DisplayProgressBar::getSerializedSize()
{
	int size = 0;
	size += sizeof(this->progress);
	size += this->boundary.getSerializedSize();
	return size;
}
int DisplayProgressBar::serialize(void* const data)
{
	printf("DisplayProgressBar::serialize()\n");
	MEMUNIT* data2 = (MEMUNIT*)data;
	packData(data2, this->progress);
	data2 += this->boundary.serialize(data2);
	return (data2 - (MEMUNIT*)data);
}
int DisplayProgressBar::deserialize(void const * const data)
{
	printf("DisplayProgressBar::deserialize()\n");
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackData(data2, this->progress);
	data2 += this->boundary.deserialize(data2);
	return (data2 - (MEMUNIT*)data);
}

} /* namespace DotMatrix */
