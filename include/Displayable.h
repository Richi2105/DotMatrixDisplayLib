/*
 * Displayable.h
 *
 *  Created on: Dec 9, 2015
 *      Author: richard
 */

#ifndef INCLUDE_DISPLAYABLE_H_
#define INCLUDE_DISPLAYABLE_H_

class Displayable {
public:
	virtual ~Displayable() = 0;

	/**
	 * this function calls the DisplayCommunication module (must be set first) to display it's content
	 */
	virtual void display() = 0;
};

#endif /* INCLUDE_DISPLAYABLE_H_ */
