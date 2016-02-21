/*
 * DotMatrixClient.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#include "DotMatrixClient.h"
#include <Telegram/Telegram.h>
#include <Telegram/TelegramObject.h>
#include <Logging/LoggerAdapter.h>
#include <math.h>
#include "../DisplayObjects/DisplayList.h"
#include "../DisplayObjects/DisplayString.h"
#include "../include/DisplayObject.h"

using namespace EventSystem;

namespace DotMatrix {

DotMatrixClient::DotMatrixClient()
{
	this->espi = new EventSystemClient(Telegram::ID_DISPLAYCLIENT);
	espi->connectToMaster();
//	espi->startReceiving();

	LoggerAdapter::initLoggerAdapter(espi);

	this->lastList = nullptr;
//	this->stringList = new std::vector<DisplayString>();

	this->xResolution = 0;
	this->yResolution = 0;

	this->espi->statemachine->setState(StateMachine::EVENTSYSTEM_STATE_RECEIVING);
	this->espi->startReceiving();

	if (this->getDisplayInfo() == -1)
	{
		//TODO: throw
	}
	this->espi->statemachine->setState(StateMachine::EVENTSYSTEM_STATE_DONE);
	this->espi->stopReceiving(true);

}

DotMatrixClient::~DotMatrixClient()
{
	delete this->espi;

}

int DotMatrixClient::getDisplayInfo()
{
	int retVal = 0;
	LoggerAdapter::log(Log::INFO, "Getting Display Information");
	Telegram t(Telegram::ID_DISPLAY);
	t.setSource(this->espi->getUniqueIdentifier());
	t.setType(Telegram::REQUEST);
	espi->send(&t);

	Telegram_Object* objTelegram = new Telegram_Object();
	DisplayPosition* pos = new DisplayPosition();
	void* data = malloc(512);

	int bytes = espi->receive(data, 5);

	printf("DotMatrixClient::getDisplayInfo(): after receive\n");
	if (bytes > 0)
	{
		objTelegram->deserialize(data, pos);


		if (objTelegram->getType() == Telegram::REQUESTANSWER)
		{
			printf("DotMatrixClient::getDisplayInfo(): setting Resolution\n");
			this->xResolution = pos->getXPosition();
			this->yResolution = pos->getYPosition();
			LoggerAdapter::log(Log::INFO, "Display Information received");
		}
		else
		{
			LoggerAdapter::log(Log::WARNING, "DotMatrixClient: Wrong telegram has been received");
		}
		printf("DotMatrixClient::getDisplayInfo(): after deserialize\n");
	}
	else
	{
		retVal = -1;
	}
	return retVal;
}
/*
void DotMatrixClient::initList(DisplayCommunication::relative_boundary boundary, DisplayCommunication::side_align side, Font::font_t font)
{
	int fontSize = Font::getFontHeight(font);
	int displayableEntries = this->yResolution / fontSize;

	this->stringList.clear();

	int xPosBegin = 0;
	int xSize = 0;

	switch (boundary)
	{
	case DisplayCommunication::FOURTH: xSize = this->xResolution / 4; break;
	case DisplayCommunication::HALF: xSize = this->xResolution / 2; break;
	case DisplayCommunication::THREE_FOURTHS: xSize = (this->xResolution / 4) * 3; break;
	case DisplayCommunication::FULL: xSize = this->xResolution; break;
	default: xSize = this->xResolution; break;
	}

	switch (side)
	{
	case DisplayCommunication::LEFT: xPosBegin = 0; break;
	case DisplayCommunication::MIDDLE: xPosBegin = (this->xResolution / 2) - (xSize / 2); break;
	case DisplayCommunication::RIGHT: xPosBegin = this->xResolution - xSize; break;
	default: xPosBegin = 0; break;
	}

	int yBegin = 0;

	for (int i=0; i<displayableEntries; i+=1)
	{
		DisplayString* entry = new DisplayString(xPosBegin, yBegin, xSize, "");
		entry->setFont(font);
		this->stringList.push_back(*entry);
		yBegin += fontSize;
	}

}
*/

void DotMatrixClient::display(DisplayList* list)
{
	if (this->lastList == list)
	{
		Telegram_Object* objTelegram = new Telegram_Object();
		objTelegram->setIdentifier("DISPLAY");
		objTelegram->setSource(this->espi->getUniqueIdentifier());
		objTelegram->setType(Telegram::DISPLAYDATA);
		DisplayObject* dobj = new DisplayObject();
		objTelegram->setObject(dobj);

		for (DisplayString* s : *(list->getEntries()))
		{
			dobj->setObject(s);
			this->espi->send(objTelegram);
		}
		delete dobj;
		delete objTelegram;

/*		int fontSize = Font::getFontHeight(list->getFont());
		int displayableEntries = this->yResolution / fontSize;

		int selectedEntry = list->getSelectedEntry();

		float center_rel = ((float) displayableEntries -1) /2;
		center_rel = list->isScrollingDown() ? center_rel + ((float) displayableEntries) /6 : center_rel - ((float) displayableEntries) /6;

		int index_start = selectedEntry - (int)rintf(center_rel);

		if (index_start < 0)
			index_start = 0;

		for (int i=0; i<displayableEntries; i+=1)
		{
			this->stringList[i].setString(list->getEntryAt(index_start));
			if (index_start == selectedEntry)
				this->stringList[i].setInverted(true);
			else
				this->stringList[i].setInverted(false);
			index_start += 1;
			objTelegram->setObject(&this->stringList[i]);
			this->espi->send(objTelegram);
		}
	}
	else
	{
		this->lastList = list;
		this->initList(list->getRelativeBoundary(), list->getSideAlign(), list->getFont());
		this->display(list);
	}
*/
	}
}

void DotMatrixClient::display(DisplayString* string)
{
	DisplayObject* dobj = new DisplayObject(string, DOBJECT_DSTRING);
	Telegram_Object* objTelegram = new Telegram_Object(Telegram::ID_DISPLAY, dobj);
	objTelegram->setSource(this->espi->getUniqueIdentifier());
	objTelegram->setType(Telegram::DISPLAYDATA);
	this->espi->send(objTelegram);
	delete dobj;
	delete objTelegram;
}

void DotMatrixClient::display(DisplayProgressBar* bar)
{
	DisplayObject* dobj = new DisplayObject(bar, DOBJECT_DPBAR);
	Telegram_Object* objTelegram = new Telegram_Object(Telegram::ID_DISPLAY, dobj);
	objTelegram->setSource(this->espi->getUniqueIdentifier());
	objTelegram->setType(Telegram::DISPLAYDATA);
	this->espi->send(objTelegram);
	delete dobj;
	delete objTelegram;
}

int DotMatrixClient::getXResolution()
{
	return this->xResolution;
}
int DotMatrixClient::getYResolution()
{
	return this->yResolution;
}

} /* namespace DotMatrix */
