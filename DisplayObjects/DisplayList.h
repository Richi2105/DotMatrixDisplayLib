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
#include "Displayable.h"
#include "../include/fonts.h"
#include "../ComModules/DisplayCommunication.h"
#include "../Positioning/DisplayBoundary.h"

namespace DotMatrix {

//TODO: not the communication module, but the list should have information about it's own entries and their absolute position on the display.

class DisplayList : public Displayable {
public:
	DisplayList(DisplayCommunication::relative_boundary b, DisplayCommunication::side_align side, int visibleRows = 0);
	virtual ~DisplayList();

	/**
	 * sets the CommunicationModule, so list can be displayed
	 */
	//static void setCommunicationModule(DisplayCommunication* dmclient);

	/**
	 * adds an entry to the list
	 * @param entry: to be added at the bottom of the list
	 * returns the size of the list
	 */
	int addEntry(std::string entry);

	/**
	 * @return: the numbers of entries inside the list
	 */
	int getSize();

	/**
	 * sets an entry to be displayed inverted
	 * @param entry: the entry number to be displayed inverted, must be smaller than the total number of entries
	 */
	void selectEntry(int entry);

    /**
     * scroll the list down step values
     * @param step the number of values to scroll down
     * @return the now selected entry
     */
    int scrollDown(int step);

    int scrollUp(int step);

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
	virtual void display();

	/**
	 * @return: the number of entries visible in the display
	 */
	int getVisibleEntries();

	/**
	 * @return: a reference to the vector with all currently visible entries
	 */
	std::vector<DisplayString*>* getEntries();

	/**
	 * @return the boundary of this list
	 */
	virtual DisplayBoundary* getBoundary();

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
	DisplayCommunication::relative_boundary getRelativeBoundary();

	/**
	 * returns the side alignment of the list
	 */
	DisplayCommunication::side_align getSideAlign();

	/**
	 * returns whether the previous selected entry was above or below the current selected entry,
	 * thus indicating if the list is scrolling down
	 * @return true if list scrolls down, false if scrolls up
	 */
	bool isScrollingDown();

	std::string getEntryAt(unsigned int index);

	std::vector<std::string>* getList();
	void setList(std::vector<std::string>* list);



private:
//	static DisplayCommunication* dmclient;

	void initList(int visibleRows);

	std::vector<DisplayString*>* visibleEntries;
	std::vector<std::string>* list;

	int entry_nr;
	int prevous_entry_nr;

	int selected_entry;
	int previous_selected_entry;

	int visibleEntryNrs;

	Font::font_t font;

	DisplayCommunication::relative_boundary boundary;
	DisplayCommunication::side_align side;
	DisplayBoundary absoluteBoundary;

};

} /* namespace DotMatrix */

#endif /* LIST_H_ */
