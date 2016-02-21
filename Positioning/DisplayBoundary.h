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

	/**
	 * change the upper left corner. Size is not retained
	 */
	void setNewBegin(DisplayPosition pos);

	/**
	 * change the lower right corner, size is not retained
	 */
	void setNewEnd(DisplayPosition pos);

	/**
	 * this changes the position of the whole box, the size stays the same
	 */
	void changePosition(DisplayPosition newStartPosition);

	/**
	 * @param otherBoundary: the boundary to compare this one with
	 * @return false if the other Boundary is bigger (or equal) in size, true if it is smaller
	 */
	bool isBigger(DisplayBoundary* otherBoundary);

	/**
	 * @param otherBoundary: the boundary to compare this one with
	 * @return true if the other Boundary is overlapping in position, false if it is completely outside the other one
	 */
	bool isOverlapping(DisplayBoundary* otherBoundary);

	/**
	 * compares the start and end points of both of the boundaries.
	 * If the start point of the other boundary is higher and lefter than this startpoint,
	 * AND if the end point of the other boundary is lower and righter than this endpoint, it is completely disguised
	 * @param otherBoundary: the boundary to compare this one with
	 * @return true if the other Boundary is bigger and completely floating over the other boundary, false if not
	 */
	bool isDisguised(DisplayBoundary* otherBoundary);

	/**
	 * whether the other boundary is above this boundary (this means the y-Position of each's beginning)
	 * @param otherBoundary: the boundary to compare this one with
	 * @return true if this boundary is below the other boundary, false if not
	 */
	bool isBelow(DisplayBoundary* otherBoundary);

	/**
	 * whether the other boundary is on the left of this boundary (this means the x-Position of each's beginning)
	 * @param otherBoundary: the boundary to compare this one with
	 * @return true if this one is more to the right than the other boundary, false if not
	 */
	bool isRight(DisplayBoundary* otherBoundary);

	/**
	 * cut a boundary in size. The boundary is cropped to a dimension so it doesn't overlap with the other boundary anymore.
	 * TODO: implement...
	 * @param otherBoundary: the boundary to crop this one with
	 * @return if the other boundary is not overlapping, false will be returned
	 */
	bool crop(DisplayBoundary* otherBoundary);

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
