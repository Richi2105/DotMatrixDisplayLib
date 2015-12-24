/*
 * TelegramDimension.h
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#ifndef TELEGRAM_TELEGRAMDIMENSION_H_
#define TELEGRAM_TELEGRAMDIMENSION_H_

#include <Telegram/Telegram.h>

class Telegram_Dimension : public EventSystem::Telegram
{
public:
	Telegram_Dimension(int x, int y);
	virtual ~Telegram_Dimension();

	int getXResolution();
	int getYResolution();

	virtual int16_t getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	int xResolution;
	int yResolution;
};

#endif /* TELEGRAM_TELEGRAMDIMENSION_H_ */
