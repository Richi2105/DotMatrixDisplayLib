#ifndef FONTS_H_INCLUDED
#define FONTS_H_INCLUDED

#include <stdint.h>
#include <string>

class Font
{
public:
	virtual ~Font() = 0;

	/**
	 * returns the name of the font.
	 */
	virtual std::string getFontName() = 0;

	/**
	 * returns the length in Pixel of a character c
	 * @param c: the requested character
	 */
	virtual int getLengthOfChar(char c) = 0;

	/**
	 * returns whether the font is mono spaced (same width over all characters)
	 */
	virtual bool isMonospace() = 0;

	/**
	 * returns the standard height of the font, not of a specific character!
	 */
	virtual int getHeight() = 0;

	/**
	 * returns the pixel data of a specific character
	 * @param data: preallocated data pointer which is written into.
	 * @param c: the requested character
	 * @param chunk: the part of the character: say the font is 16 pixel in height, and you specify chunk as 8,
	 * 				 you get the pixel data of the lower half of the character, since a char can only hold 8 bit.
	 * 				 chunk = 0: upper half
	 */
	virtual int getCharPixel(uint8_t* const data, char c, int chunk) = 0;

	/**
	 * returns the pixel data of a specific character. Fonts which are less than 32 pixels in height will be returned top aligned.
	 * @param data: preallocated data pointer which is written into.
	 * @param c: the requested character
	 */
	virtual int getCharPixel(uint32_t* const data, char c) = 0;

	static enum font_t {standard_8_mono, standard_6_mono, standard_6} fontType;
	//more to be added...

	static int getFontHeight(Font::font_t type);
};



#endif // FONTS_H_INCLUDED
