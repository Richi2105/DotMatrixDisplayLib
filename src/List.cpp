/*
 * List.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#include "../include/List.h"

namespace DotMatrix {

DotMatrixClient* List::dmclient = nullptr;

List::List(DotMatrixClient::relative_boundary b, DotMatrixClient::side_align side)
{
	if (List::dmclient == nullptr)
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

List::~List() {
	// TODO Auto-generated destructor stub
}

void List::setDotMatrixClient(DotMatrixClient* dmclient)
{
	List::dmclient = dmclient;
}

int List::addEntry(std::string entry)
{
	this->list.push_back(entry);
	this->entry_nr += 1;
	return this->entry_nr;
}

void List::selectEntry(int entry)
{
	if (entry < this->entry_nr)
	{
		this->previous_selected_entry = this->selected_entry;
		this->selected_entry = entry;
	}

}

int List::getSelectedEntry()
{
	return this->selected_entry;
}

void List::clear()
{
	//TODO clear vector, call display();
}

void List::display()
{
	List::dmclient->display(this);
}

void List::setFont(Font::font_t type)
{
	this->font = type;
}

Font::font_t List::getFont()
{
	return this->font;
}

DotMatrixClient::relative_boundary List::getBoundary()
{
	return this->boundary;
}

DotMatrixClient::side_align List::getSideAlign()
{
	return this->side;
}

bool List::isScrollingDown()
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

} /* namespace DotMatrix */


