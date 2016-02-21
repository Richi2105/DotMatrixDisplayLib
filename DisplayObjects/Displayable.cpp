/*
 * Displayable.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: richard
 */

#include "Displayable.h"

namespace DotMatrix
{

DisplayCommunication* Displayable::dispCom = nullptr;

Displayable::~Displayable()
{

}

void Displayable::setCommunicationModule(DisplayCommunication* module)
{
	Displayable::dispCom = module;
}

} /* namespace DotMatrix */
