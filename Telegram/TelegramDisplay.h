/*
 * TelegramDisplay.h
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#ifndef TELEGRAM_TELEGRAMDISPLAY_H_
#define TELEGRAM_TELEGRAMDISPLAY_H_

#include <Telegram/Telegram.h>
#include "../include/DisplayString.h"

class Telegram_Display: public Telegram {
public:
	Telegram_Display(DisplayString s);
	Telegram_Display();
	virtual ~Telegram_Display();

	DisplayString* getDisplayString();

	virtual int16_t getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	DisplayString dString;
};

#endif /* TELEGRAM_TELEGRAMDISPLAY_H_ */
