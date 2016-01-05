/*
 * List.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#include "../include/DisplayList.h"

namespace DotMatrix {

DisplayCommunication* DisplayList::dmclient = nullptr;

DisplayList::DisplayList(DisplayCommunication::relative_boundary b, DisplayCommunication::side_align side)
{
	if (DisplayList::dmclient == nullptr)
	{
		;//TODO: check
	}

	this->side = side;
	this->boundary = b;
	this->font = Font::standard_8_mono;

	this->entry_nr = 0;
	this->prevous_entry_nr = 0;
	this->selected_entry = -1;
	this->previous_selected_entry = -1;

}

DisplayList::~DisplayList() {
	// TODO Auto-generated destructor stub
}

void DisplayList::setCommunicationModule(DisplayCommunication* dmclient)
{
	DisplayList::dmclient = dmclient;
}

int DisplayList::addEntry(std::string entry)
{
	this->list.push_back(entry);
	this->entry_nr += 1;
	return this->entry_nr;
}

int DisplayList::getSize()
{
	return this->list.size();
}

void DisplayList::selectEntry(int entry)
{
	if (entry < this->entry_nr)
	{
		this->previous_selected_entry = this->selected_entry;
		this->selected_entry = entry;
	}

}

int DisplayList::getSelectedEntry()
{
	return this->selected_entry;
}

void DisplayList::clear()
{
	//TODO clear vector, call display();
}

void DisplayList::display()
{
	if (DisplayList::dmclient != nullptr)
		DisplayList::dmclient->display(this);
}

void DisplayList::setFont(Font::font_t type)
{
	this->font = type;
}

Font::font_t DisplayList::getFont()
{
	return this->font;
}

DisplayCommunication::relative_boundary DisplayList::getBoundary()
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

std::string DisplayList::getEntryAt(int index)
{
	if (index < this->list.size() && index >= 0)
		return list[index];
	else
		return " ";
}

} /* namespace DotMatrix */


