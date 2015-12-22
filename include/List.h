/*
 * List.h
 *
 *  Created on: Dec 21, 2015
 *      Author: richard
 */

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <vector>
#include "fonts.h"
#include "DotMatrixClient.h"

namespace DotMatrix {

class List {
public:
	List(DotMatrixClient::relative_boundary b, DotMatrixClient::side_align side);
	virtual ~List();

	/**
	 * sets the DotMatrixClient, so list can be displayed
	 */
	static void setDotMatrixClient(DotMatrixClient* dmclient);

	/**
	 * adds an entry to the list
	 * @param entry: to be added at the bottom of the list
	 * returns the size of the list
	 */
	int addEntry(std::string entry);

	/**
	 * sets an entry to be displayed inverted
	 * @param entry: the entry number to be displayed inverted, must be smaller than the total number of entries
	 */
	void selectEntry(int entry);

	/**
	 * returns the index of the selected entry
	 */
	int getSelectedEntry();

	/**
	 * clears the list, calls display();
	 */
	void clear();

	/**
	 * displays the list on the display, with the selected entry in focus
	 * this must be called when changes are done to the list (except for clear())
	 */
	void display();

	/**
	 * sets the font of the list.
	 * @param type: the font type identifier
	 */
	void setFont(Font::font_t type);

	/**
	 * returns the font identifier
	 */
	Font::font_t getFont();

	/**
	 * returns the relative size in x-direction of the list
	 */
	DotMatrixClient::relative_boundary getBoundary();

	/**
	 * returns the side alignment of the list
	 */
	DotMatrixClient::side_align getSideAlign();

	/**
	 * returns whether the previous selected entry was above or below the current selected entry,
	 * thus indicating if the list is scrolling down
	 * @return true if list scrolls down, false if scrolls up
	 */
	bool isScrollingDown();

	std::string getEntryAt(int index)
	{
		return list[index];
	}

private:
	static DotMatrixClient* dmclient;

	std::vector<std::string> list;

	int entry_nr;
	int prevous_entry_nr;

	int selected_entry;
	int previous_selected_entry;

	Font::font_t font;

	DotMatrixClient::relative_boundary boundary;
	DotMatrixClient::side_align side;

};

} /* namespace DotMatrix */

#endif /* LIST_H_ */
