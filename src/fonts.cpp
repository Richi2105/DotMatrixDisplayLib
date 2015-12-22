/*
 * fonts.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: richard
 */

#include "../include/fonts.h"

Font::~Font()
{

}

int Font::getFontHeight(Font::font_t type)
{
	int height;
	switch (type)
	{
	case Font::standard_6: height = 6; break;
	case Font::standard_6_mono: height = 6; break;
	case Font::standard_8_mono: height = 8; break;
	default: height = 0; break;
	}
	return height;
}


