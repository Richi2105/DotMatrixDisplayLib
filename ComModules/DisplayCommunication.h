/*
 * DisplayCommunication.h
 *
 *  Created on: Dec 25, 2015
 *      Author: richard
 */

#ifndef INCLUDE_DISPLAYCOMMUNICATION_H_
#define INCLUDE_DISPLAYCOMMUNICATION_H_



namespace DotMatrix
{

class DisplayList;
class DisplayString;
class DisplayProgressBar;

class DisplayCommunication {
public:

	/**
	 * this represents the boundary of an displayable object (i.e. the size in x_direction)
	 */
	static enum relative_boundary {FOURTH, HALF, THREE_FOURTHS, FULL} boundary;

	/**
	 * this represents the relative y-position of an displayable object
	 */
	static enum relative_YPosition {TOP, TOP_CENTER, CENTER, BOTTOM_CENTER, BOTTOM} yPosition;

	/**
	 * this represents the alignment of an displayable object
	 */
	static enum side_align {LEFT, MIDDLE, RIGHT} align;

	virtual int getXResolution() = 0;
	virtual int getYResolution() = 0;

	virtual void display(DisplayList* list) = 0;
	virtual void display(DisplayString* string) = 0;
	virtual void display(DisplayProgressBar* bar) = 0;
//	virtual void sendToDisplay(int xPos, int yPos, int numOfBytes, unsigned char* data, bool inverted) = 0;
	virtual ~DisplayCommunication();

protected:
	int xResolution;
	int yResolution;

};

} /* namespace DotMatrix */

#endif /* INCLUDE_DISPLAYCOMMUNICATION_H_ */
