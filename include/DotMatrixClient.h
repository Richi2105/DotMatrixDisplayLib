/*
 * DotMatrixClient.h
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#ifndef DOTMATRIXCLIENT_H_
#define DOTMATRIXCLIENT_H_

#include <EventSystemParticipantImpl.h>

namespace DotMatrix {

class List;

class DotMatrixClient {
public:
	DotMatrixClient();
	virtual ~DotMatrixClient();

	/**
	 * this represents the boundary of an displayable object (e.g. the size in x_direction)
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

	void display(List* list);

private:
	void getDisplayInfo();

	int xResolution, yResolution;

	EventSystemParticipantImpl* espi;
};

} /* namespace DotMatrix */

#endif /* DOTMATRIXCLIENT_H_ */
