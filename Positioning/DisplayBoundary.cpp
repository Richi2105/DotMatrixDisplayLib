/*
 * DisplayBoundary.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: richard
 */

#include "DisplayBoundary.h"

DisplayBoundary::DisplayBoundary(int xPosBegin, int yPosBegin, int xPosEnd, int yPosEnd) : begin(xPosBegin, yPosBegin), end(xPosEnd, yPosEnd)
{
	;
}
DisplayBoundary::DisplayBoundary(DisplayPosition begin, DisplayPosition end)
{
	this->end = end;
	this->begin = begin;
}
DisplayBoundary::DisplayBoundary() : begin(), end()
{
	;
}
DisplayBoundary::~DisplayBoundary()
{
	;
}

void DisplayBoundary::setNewBegin(DisplayPosition pos)
{
	this->begin = pos;
}
void DisplayBoundary::setNewEnd(DisplayPosition pos)
{
	this->end = pos;
}

void DisplayBoundary::changePosition(DisplayPosition newStartPosition)
{
	int xdev, ydev;
	xdev = this->end.xPosition - this->begin.xPosition;
	ydev = this->end.yPosition - this->begin.yPosition;
	this->begin = newStartPosition;
	this->end.setXPosition(this->end.xPosition+xdev);
	this->end.setYPosition(this->end.yPosition+ydev);
}

bool DisplayBoundary::isBigger(DisplayBoundary* otherBoundary)
{
	bool retval = false;

	int xdev_this = this->begin.xPosition - this->end.xPosition;
	int ydev_this = this->begin.yPosition - this->end.yPosition;

	int xdev_other = otherBoundary->begin.xPosition - otherBoundary->end.xPosition;
	int ydev_other = otherBoundary->begin.yPosition - otherBoundary->end.yPosition;

	int square_this = xdev_this * ydev_this;
	int square_other = xdev_other * ydev_other;

	if (square_this > square_other)
		retval = true;

	return retval;
}

bool DisplayBoundary::isOverlapping(DisplayBoundary* otherBoundary)
{
	bool retval = false;

	if (this->isBelow(otherBoundary))
	{
		if (otherBoundary->end.xPosition >= this->begin.xPosition)
			retval = true;
		if (otherBoundary->end.yPosition >= this->begin.yPosition)
			retval = true;
	}
	else
	{
		if (otherBoundary->begin.xPosition < this->end.xPosition)
			retval = true;
		if (otherBoundary->begin.yPosition < this->end.yPosition)
			retval = true;
	}

	return retval;
}

bool DisplayBoundary::isDisguised(DisplayBoundary* otherBoundary)
{
	bool retval = false;

	if (otherBoundary->begin.xPosition <= this->begin.xPosition && otherBoundary->begin.yPosition <= this->begin.yPosition)
	{
		if (otherBoundary->end.xPosition >= this->end.xPosition && otherBoundary->end.yPosition >= this->end.yPosition)
		{
			retval = true;
		}
	}
	return retval;
}

bool DisplayBoundary::isBelow(DisplayBoundary* otherBoundary)
{
	bool retval = false;
	if (otherBoundary->begin.yPosition < this->begin.yPosition)
		retval = true;
	return retval;
}

bool DisplayBoundary::isRight(DisplayBoundary* otherBoundary)
{
	bool retval = false;
	if (otherBoundary->begin.xPosition < this->begin.xPosition)
		retval = true;
	return retval;
}

int DisplayBoundary::getXPosBegin()
{
	return this->begin.getXPosition();
}
int DisplayBoundary::getXPosEnd()
{
	return this->end.getXPosition();
}
int DisplayBoundary::getYPosBegin()
{
	return this->begin.getYPosition();
}
int DisplayBoundary::getYPosEnd()
{
	return this->end.getYPosition();
}

void DisplayBoundary::setXPosBegin(int xBegin)
{
	this->begin.setXPosition(xBegin);
}
void DisplayBoundary::setXPosEnd(int xEnd)
{
	this->end.setXPosition(xEnd);
}
void DisplayBoundary::setYPosBegin(int yBegin)
{
	this->begin.setYPosition(yBegin);
}
void DisplayBoundary::setYPosEnd(int yEnd)
{
	this->end.setYPosition(yEnd);
}

DisplayPosition DisplayBoundary::getBegin()
{
	return this->begin;
}
DisplayPosition DisplayBoundary::getEnd()
{
	return this->end;
}

int DisplayBoundary::getSerializedSize()
{
	int16_t size = 0;
	size += this->begin.getSerializedSize();
	size += this->end.getSerializedSize();
	return size;
}
int DisplayBoundary::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	data2 += this->begin.serialize(data2);
	data2 += this->end.serialize(data2);

	return this->getSerializedSize();
}
int DisplayBoundary::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	data2 += this->begin.deserialize(data2);
	data2 += this->end.deserialize(data2);

	return this->getSerializedSize();
}

