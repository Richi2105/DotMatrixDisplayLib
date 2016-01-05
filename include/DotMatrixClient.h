/*
 * DotMatrixClient.h
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#ifndef DOTMATRIXCLIENT_H_
#define DOTMATRIXCLIENT_H_

#include <vector>
#include <EventSystemClient.h>
#include "DisplayCommunication.h"

using namespace EventSystem;

namespace DotMatrix {

class DisplayList;

class DotMatrixClient : public DisplayCommunication {
public:
	DotMatrixClient();
	virtual ~DotMatrixClient();

	virtual void display(DisplayList* list);
	virtual void display(DisplayString* string);

	int getXResolution();
	int getYResolution();

private:
	void getDisplayInfo();
	void initList(DisplayCommunication::relative_boundary boundary, DisplayCommunication::side_align side, Font::font_t font);

	std::vector<DisplayString> stringList;
	DisplayList* lastList;

	int xResolution, yResolution;

	EventSystemClient* espi;
};

} /* namespace DotMatrix */

#endif /* DOTMATRIXCLIENT_H_ */
