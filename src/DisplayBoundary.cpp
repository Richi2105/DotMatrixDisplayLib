/*
 * DisplayBoundary.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: richard
 */

#include "/home/richard/workspace/DotMatrixDisplayLib/include/DisplayBoundary.h"

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

int16_t DisplayBoundary::getSerializedSize()
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

