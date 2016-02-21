/*
 * Displayable.h
 *
 *  Created on: Dec 9, 2015
 *      Author: richard
 */

#ifndef DISPLAYOBJECTS_DISPLAYABLE_H_
#define DISPLAYOBJECTS_DISPLAYABLE_H_

#include <Serializeable.h>
#include "../ComModules/DisplayCommunication.h"
//#include "../Positioning/DisplayBoundary.h"

class DisplayBoundary;
//class DisplayCommunication;

namespace DotMatrix {

class Displayable {
public:
	virtual ~Displayable() = 0;

	/**
	 * this function calls the DisplayCommunication module (must be set first) to display it's content
	 */
	virtual void display() = 0;

	/**
	 * @return the boundary box of this object
	 */
	virtual DisplayBoundary* getBoundary() = 0;

    /**
     * set the DisplayCommunication module. This sets the module for all DisplayStrings
     */
    static void setCommunicationModule(DisplayCommunication* module);

protected:
	static DisplayCommunication* dispCom;
};

} /* namespace DotMatrix */

#endif /* DISPLAYOBJECTS_DISPLAYABLE_H_ */
