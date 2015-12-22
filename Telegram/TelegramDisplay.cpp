/*
 * TelegramDisplay.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#include "TelegramDisplay.h"

Telegram_Display::Telegram_Display(DisplayString s) : Telegram("DISPLAY")
{
	this->dString = s;
}

Telegram_Display::Telegram_Display() : Telegram("DISPLAY"), dString()
{

}

Telegram_Display::~Telegram_Display() {
	// TODO Auto-generated destructor stub
}

int16_t Telegram_Display::getSerializedSize()
{
	int16_t size = 0;
	size += Telegram::getSerializedSize();
	size += this->dString.getSerializedSize();

	return size;
}
int Telegram_Display::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	data2 += Telegram::serialize(data2);
	data2 += this->dString.serialize(data2);

	return Telegram::getSerializedSize();
}
int Telegram_Display::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	data2 += Telegram::deserialize(data2);
	data2 += this->dString.deserialize(data2);

	return Telegram::getSerializedSize();
}

