/*
 * DisplayBoundary.h
 *
 *  Created on: Dec 8, 2015
 *      Author: richard
 */

#ifndef INCLUDE_DISPLAYBOUNDARY_H_
#define INCLUDE_DISPLAYBOUNDARY_H_

#include "DisplayPosition.h"

class DisplayBoundary : public Serializeable
{
public:
	DisplayBoundary(int xPosBegin, int yPosBegin, int xPosEnd, int yPosEnd);
	DisplayBoundary(DisplayPosition begin, DisplayPosition end);
	DisplayBoundary();
	virtual ~DisplayBoundary();

	void setNewBegin(DisplayPosition pos);
	void setNewEnd(DisplayPosition pos);

	int getXPosBegin();
	int getXPosEnd();
	int getYPosBegin();
	int getYPosEnd();

	void setXPosBegin(int xBegin);
	void setXPosEnd(int xEnd);
	void setYPosBegin(int yBegin);
	void setYPosEnd(int yEnd);

	DisplayPosition getBegin();
	DisplayPosition getEnd();

    virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	DisplayPosition begin;
	DisplayPosition end;
};

#endif /* INCLUDE_DISPLAYBOUNDARY_H_ */
