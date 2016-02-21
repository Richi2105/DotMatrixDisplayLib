#ifndef DISPLAYSTRING_H
#define DISPLAYSTRING_H

#include "../Positioning/DisplayBoundary.h"
#include "../include/Characters.h"
#include "../include/fonts.h"
#include <string>
#include "DisplayableSerializeable.h"
#include "../ComModules/DisplayCommunicationVoid.h"

#define DISPLAYSTRINGSIZE 30

namespace DotMatrix
{

class DisplayString : public DisplayableSerializeable
{
    public:
		/**
		 * Constructs a DisplayString object
		 * The font is set to Standard_8_mono
		 * @param begin: upper left corner of the string, e.g. the Position
		 * @param end: Lower right corner of the string. if the boundary is smaller than the graphic of the string, the string becomes a scrolling string.
		 * 				The height should match the font height in pixel, the standard is 8 @see fonts.h
		 * @param str: the message to be displayed
		 */
        DisplayString(DisplayPosition begin, DisplayPosition end, std::string str);

        /**
         * Constructs a DisplayString object
		 * The font is set to Standard_8_mono, the height is set according to the font.
		 * @param x: the start position of the string in x direction
		 * @param y: the top position of the string in y direction
		 * @param length: the length in pixels to be displayed. if the length is smaller than the graphic of the string, the string becomes a scrolling string.
		 * @param str: the message to be displayed
         */
        DisplayString(int x, int y, int length, std::string str);
        DisplayString();
        virtual ~DisplayString();

        /**
         * set the DisplayCommunication module. This sets the module for all DisplayStrings
         */
        //static void setCommunicationModule(DisplayCommunication* module);

        /**
         * returns the position of the string (upper left corner)
         */
        DisplayPosition getPositionBegin();

        /**
         * returns the lower right corner of the string
         */
        DisplayPosition getPositionEnd();

        /**
         * sets the string to a new position, the dimensions determined by the end position are kept.
         */
        void setPosition(DisplayPosition pos);

        /**
         * returns the string to be displayed
         */
        std::string getString();

        /**
         * sets the string to be displayed
         */
        void setString(std::string str);

        /**
         * sets the font of the string
         */
        void setFont(Font::font_t f);

        /**
         * returns the font of the string
         */
        Font::font_t getFont();

        /**
         * returns whether the string should be displayed inverted
         */
        bool isInverted();

        /**
         * sets the string to be displayed inverted
         */
        void setInverted(bool invert);

        virtual void display();
        virtual DisplayBoundary* getBoundary();

        virtual int getSerializedSize();
    	virtual int serialize(void* const data);
    	virtual int deserialize(void const * const data);

    protected:
    private:
//    	void setCommunicationModule();
    	bool inverted;
//    	Font* font;
    	Font::font_t fontType;
//      static DisplayCommunication* communicationModule;
        DisplayBoundary box;
        char str[DISPLAYSTRINGSIZE];
};

} /* namespace DotMatrix */

#endif // DISPLAYSTRING_H
