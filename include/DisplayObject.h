/*
 * DisplayObject.h
 *
 *  Created on: Feb 8, 2016
 *      Author: richard
 */

#ifndef INCLUDE_DISPLAYOBJECT_H_
#define INCLUDE_DISPLAYOBJECT_H_

#include "../DisplayObjects/DisplayableSerializeable.h"

#include "../DisplayObjects/Displayable.h"
#include "../DisplayObjects/DisplayList.h"
#include "../DisplayObjects/DisplayProgressBar.h"
#include "../DisplayObjects/DisplayString.h"

//#define DOBJECT_DLIST 1
#define DOBJECT_DSTRING 2
#define DOBJECT_DPBAR 3

namespace DotMatrix {

class DisplayObject: public Serializeable {
public:
	DisplayObject(DisplayableSerializeable* object, int objectType);
	DisplayObject();
	virtual ~DisplayObject();

//	void setObject(DisplayList* list);
	void setObject(DisplayString* string);
	void setObject(DisplayProgressBar* bar);

	Displayable* getObject();
	uint8 getObjectType();

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	uint8 objectType;
	DisplayableSerializeable* object;
};

} /* namespace DotMatrix */

#endif /* INCLUDE_DISPLAYOBJECT_H_ */
