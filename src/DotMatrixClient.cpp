/*
 * DotMatrixClient.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#include "../include/DisplayString.h"
#include "../include/DotMatrixClient.h"
#include "../include/List.h"
#include "../Telegram/TelegramDimension.h"
#include "../Telegram/TelegramDisplay.h"

#include <Telegram/Telegram.h>
#include <Logging/LoggerAdapter.h>

namespace DotMatrix {

DotMatrixClient::DotMatrixClient()
{
	this->espi = new EventSystemParticipantImpl("DISPLAY_CLIENT");
	espi->connectToMaster();

	LoggerAdapter::initLoggerAdapter(espi);

	this->xResolution = 0;
	this->yResolution = 0;

	this->getDisplayInfo();

}

DotMatrixClient::~DotMatrixClient()
{

}

void DotMatrixClient::getDisplayInfo()
{
	//TODO: send telegram to display, receive information
	Telegram t("DISPLAY");
	t.setType(REQUEST);
	espi->send(&t);

	Telegram_Dimension td(0, 0);
	void* data = malloc(td.getSerializedSize());

	espi->receive(data, false);

	td.deserialize(data);

	if (td.getType() == DISPLAYDIMENSION)
	{
		this->xResolution = td.getXResolution();
		this->yResolution = td.getYResolution();
	}
	else
	{
		LoggerAdapter::log(LoggerAdapter::WARNING, "DotMatrixClient: Wrong telegram has been received");
	}
}

void DotMatrixClient::display(List* list)
{
	int fontSize = Font::getFontHeight(list->getFont());
	int displayableEntries = this->yResolution / fontSize;

	int selectedEntry = list->getSelectedEntry();

	double center_rel = ((double) displayableEntries -1) /2;
	center_rel = list->isScrollingDown() ? center_rel + ((double) displayableEntries) /4 : center_rel - ((double) displayableEntries) /4;

	int index_start = selectedEntry - (int) center_rel;

	int xPosBegin = 0;
	int xSize = 0;

	switch (list->getBoundary())
	{
	case DotMatrixClient::FOURTH: xSize = this->xResolution / 4; break;
	case DotMatrixClient::HALF: xSize = this->xResolution / 2; break;
	case DotMatrixClient::THREE_FOURTHS: xSize = (this->xResolution / 4) * 3; break;
	case DotMatrixClient::FULL: xSize = this->xResolution; break;
	default: xSize = this->xResolution; break;
	}

	switch (list->getSideAlign())
	{
	case DotMatrixClient::LEFT: xPosBegin = 0; break;
	case DotMatrixClient::MIDDLE: xPosBegin = (this->xResolution / 2) - (xSize / 2); break;
	case DotMatrixClient::RIGHT: xPosBegin = this->xResolution - xSize; break;
	default: xPosBegin = 0; break;
	}

	int yBegin = 0;

	for (int i=0; i<displayableEntries; i+=1)
	{
		DisplayString entry(xPosBegin, yBegin, xSize, list->getEntryAt(index_start++));
		entry.setFont(list->getFont());
		if (index_start == selectedEntry)
		{
			entry.setInverted(true);
		}
		Telegram_Display td(entry);
		espi->send(&td);

		yBegin += fontSize;
	}
}

} /* namespace DotMatrix */
