/*
 * DisplayableSerializeable.h
 *
 *  Created on: Feb 18, 2016
 *      Author: richard
 */

#ifndef DISPLAYOBJECTS_DISPLAYABLESERIALIZEABLE_H_
#define DISPLAYOBJECTS_DISPLAYABLESERIALIZEABLE_H_

#include <Serializeable.h>
#include "Displayable.h"

namespace DotMatrix {

class DisplayableSerializeable: public Serializeable, public Displayable {

public:
	virtual ~DisplayableSerializeable();
};

} /* namespace DotMatrix */

#endif /* DISPLAYOBJECTS_DISPLAYABLESERIALIZEABLE_H_ */
