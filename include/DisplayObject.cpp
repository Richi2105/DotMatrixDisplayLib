/*
 * DisplayObject.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: richard
 */

#include "DisplayObject.h"

namespace DotMatrix {

DisplayObject::DisplayObject(DisplayableSerializeable* object, int objectType)
{
	this->object = object;
	this->objectType = (uint8) objectType;
}

DisplayObject::DisplayObject()
{
	this->object = nullptr;
	this->objectType = 0;
}

DisplayObject::~DisplayObject() {
	// TODO Auto-generated destructor stub
}
/* nope!
void DisplayObject::setObject(DisplayList* list)
{
	this->object = list;
	this->objectKind = DOBJECT_DLIST;
}
*/
void DisplayObject::setObject(DisplayString* string)
{
	this->object = string;
	this->objectType = DOBJECT_DSTRING;
}
void DisplayObject::setObject(DisplayProgressBar* bar)
{
	this->object = bar;
	this->objectType = DOBJECT_DPBAR;
}

Displayable* DisplayObject::getObject()
{
	return (Displayable*)this->object;
}

uint8 DisplayObject::getObjectType()
{
	return this->objectType;
}

int DisplayObject::getSerializedSize()
{
	int size = 0;
	size += sizeof(this->objectType);
	if (this->object != nullptr)
		size += this->object->getSerializedSize();
	return size;
}
int DisplayObject::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*) data;
	packData(data2, this->objectType);
	if (this->object != nullptr)
		data2 += this->object->serialize(data2);
	return (data2 - (MEMUNIT*)data);
}
int DisplayObject::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*) data;
	unpackData(data2, this->objectType);
	switch (this->objectType) {
//	case DOBJECT_DLIST: this->object = new DisplayList(0,0,0); break;
	case DOBJECT_DSTRING: this->object = new DisplayString(); break;
	case DOBJECT_DPBAR: this->object = new DisplayProgressBar(); break;
	default: this->object = nullptr; break;
	}
	if (this->object != nullptr)
		data2 += this->object->deserialize(data2);
	return (data2 - (MEMUNIT*)data);
}

} /* namespace DotMatrix */
