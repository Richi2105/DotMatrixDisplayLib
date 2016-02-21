/*
 * DisplayProgressBar.h
 *
 *  Created on: Feb 8, 2016
 *      Author: richard
 */

#ifndef DISPLAYOBJECTS_DISPLAYPROGRESSBAR_H_
#define DISPLAYOBJECTS_DISPLAYPROGRESSBAR_H_

#include <OS_DEF.h>

#include "DisplayableSerializeable.h"
#include "../Positioning/DisplayPosition.h"
#include "../Positioning/DisplayBoundary.h"

namespace DotMatrix {

/**
 *  <========||===>
 *  what it may look like
 *  double bars represent the progress pointer
 */
class DisplayProgressBar : public DisplayableSerializeable {
public:
	DisplayProgressBar(DisplayPosition pos, int length, int height);
	DisplayProgressBar(DisplayBoundary boundary);
	DisplayProgressBar();
	virtual ~DisplayProgressBar();

	/**
	 * set the progress pointer to a percentual value
	 * @param percent: float value, max is 1.0
	 */
	void setProgressPercent(float percent);

	/**
	 * @return the relative pixel position of the progress pointer
	 */
	int getProgressPointerPosition();

	virtual void display();

	virtual DisplayBoundary* getBoundary();

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	DisplayBoundary boundary;
	uint8 progress;
};

} /* namespace DotMatrix */

#endif /* DISPLAYOBJECTS_DISPLAYPROGRESSBAR_H_ */
