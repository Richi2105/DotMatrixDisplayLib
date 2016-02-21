/*
 * List.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#include <math.h>

#include "DisplayList.h"
#include "DisplayString.h"

namespace DotMatrix {

//DisplayCommunication* DisplayList::dmclient = nullptr;

DisplayList::DisplayList(DisplayCommunication::relative_boundary b, DisplayCommunication::side_align side, int visibleRows)
{
	this->list = new std::vector<std::string>();
	this->visibleEntries = new std::vector<DisplayString*>;

	this->side = side;
	this->boundary = b;
	this->font = Font::standard_8_mono;

	this->entry_nr = 0;
	this->prevous_entry_nr = 0;
	this->selected_entry = -1;
	this->previous_selected_entry = -1;
	this->visibleEntryNrs = 0;

	if (Displayable::dispCom != nullptr)
	{
		this->initList(visibleRows);
	}

}

DisplayList::~DisplayList() {
	for (DisplayString* d : *this->visibleEntries)
		delete d;
	delete this->visibleEntries;
}
/*
void DisplayList::setCommunicationModule(DisplayCommunication* dmclient)
{
	DisplayList::dmclient = dmclient;
}
*/

void DisplayList::initList(int visibleRows)
{
	int fontSize = Font::getFontHeight(font);
	this->visibleEntryNrs = Displayable::dispCom->getYResolution() / fontSize;

	if (visibleRows > 0)
	{
		this->visibleEntryNrs = visibleRows < this->visibleEntryNrs ? visibleRows : this->visibleEntryNrs;
	}


	int xPosBegin = 0;
	int xSize = 0;

	switch (boundary)
	{
	case DisplayCommunication::FOURTH: xSize = Displayable::dispCom->getXResolution() / 4; break;
	case DisplayCommunication::HALF: xSize = Displayable::dispCom->getXResolution() / 2; break;
	case DisplayCommunication::THREE_FOURTHS: xSize = (Displayable::dispCom->getXResolution() / 4) * 3; break;
	case DisplayCommunication::FULL: xSize = Displayable::dispCom->getXResolution(); break;
	default: xSize = Displayable::dispCom->getXResolution(); break;
	}

	switch (side)
	{
	case DisplayCommunication::LEFT: xPosBegin = 0; break;
	case DisplayCommunication::MIDDLE: xPosBegin = (Displayable::dispCom->getXResolution() / 2) - (xSize / 2); break;
	case DisplayCommunication::RIGHT: xPosBegin = Displayable::dispCom->getXResolution() - xSize; break;
	default: xPosBegin = 0; break;
	}

	this->absoluteBoundary.setXPosBegin(xPosBegin);
	this->absoluteBoundary.setXPosEnd(xPosBegin + xSize);

	int yBegin = this->absoluteBoundary.getYPosBegin();

	for (int i=0; i<this->visibleEntryNrs; i+=1)
	{
		DisplayString* entry = new DisplayString(xPosBegin, yBegin, xSize, "");
		entry->setFont(font);
		this->visibleEntries->push_back(entry);
		yBegin += fontSize;
	}
	this->absoluteBoundary.setYPosEnd(yBegin);
}

int DisplayList::addEntry(std::string entry)
{
	this->list->push_back(entry);
	this->entry_nr += 1;
	return this->entry_nr;
}

int DisplayList::getSize()
{
	return this->list->size();
}

void DisplayList::selectEntry(int entry)
{
    if (entry < this->getSize() && entry >= 0)
    {
        this->previous_selected_entry = this->selected_entry;
        this->selected_entry = entry;
    }
    else if (entry >= this->getSize())
        selectEntry(this->getSize()-1);
    else if (entry < 0)
        selectEntry(0);

}

int DisplayList::scrollDown(int step)
{
    this->selectEntry(this->selected_entry + step);
    return this->selected_entry;
}

int DisplayList::scrollUp(int step)
{
    this->selectEntry(this->selected_entry - step);
    return this->selected_entry;
}

int DisplayList::getSelectedEntry()
{
	return this->selected_entry;
}

void DisplayList::clear()
{
	this->list->clear();
	this->selected_entry = -1;
	this->previous_selected_entry = -1;
	//TODO clear vector, call display();
}

void DisplayList::display()
{
	if (Displayable::dispCom != nullptr)
	{
		float center_rel = ((float) this->visibleEntryNrs -1) /2;
		center_rel = this->isScrollingDown() ? center_rel + ((float) this->visibleEntryNrs) /6 : center_rel - ((float) this->visibleEntryNrs) /6;

		int index_start = this->selected_entry - (int)rintf(center_rel);

		if (index_start < 0)
			index_start = 0;

		for (int i=0; i<this->visibleEntryNrs; i+=1)
		{
			this->visibleEntries->at(i)->setString(this->getEntryAt(index_start));
			if (index_start == this->selected_entry)
				this->visibleEntries->at(i)->setInverted(true);
			else
				this->visibleEntries->at(i)->setInverted(false);
			index_start += 1;
		}
		Displayable::dispCom->display(this);
	}
}

int DisplayList::getVisibleEntries()
{
	return this->visibleEntryNrs;
}

std::vector<DisplayString*>* DisplayList::getEntries()
{
	return this->visibleEntries;
}

DisplayBoundary* DisplayList::getBoundary()
{
	return &this->absoluteBoundary;
}

void DisplayList::setFont(Font::font_t type)
{
	this->font = type;
}

Font::font_t DisplayList::getFont()
{
	return this->font;
}

DisplayCommunication::relative_boundary DisplayList::getRelativeBoundary()
{
	return this->boundary;
}

DisplayCommunication::side_align DisplayList::getSideAlign()
{
	return this->side;
}

bool DisplayList::isScrollingDown()
{
	if (this->selected_entry <= this->previous_selected_entry)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::string DisplayList::getEntryAt(unsigned int index)
{
	if (index < this->list->size())
		return list->at(index);
	else
		return " ";
}

std::vector<std::string>* DisplayList::getList()
{
	return this->list;
}
void DisplayList::setList(std::vector<std::string>* list)
{
	this->selected_entry = -1;
	this->previous_selected_entry = -1;
	this->list = list;
}

} /* namespace DotMatrix */


