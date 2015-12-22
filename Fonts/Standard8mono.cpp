/*
 * Standard8mono.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: richard
 */

#include "Standard8mono.h"

Standard_8_mono::Standard_8_mono() {
	// TODO Auto-generated constructor stub

}

Standard_8_mono::~Standard_8_mono() {
	// TODO Auto-generated destructor stub
}

std::string Standard_8_mono::getFontName()
{
	return "Standart_8_mono";
}
int Standard_8_mono::getLengthOfChar(char c)
{
	return 5;
}
bool Standard_8_mono::isMonospace()
{
	return true;
}
int Standard_8_mono::getHeight()
{
	return 8;
}
int Standard_8_mono::getCharPixel(uint8_t* const data, char c, int chunk)
{
	uint8_t* data2 = data;
	int i;
	for(i=0; i<5; i+=1)
	{
		*(data2 + i) = (this->characterMap[c-32][i] << chunk) & this->Mask8Pix;
	}
	return i;
}
int Standard_8_mono::getCharPixel(uint32_t* const data, char c)
{
	uint32_t* data2 = data;
	int i;
	for(i=0; i<5; i+=1)
	{
		*(data2 + i) = this->characterMap[c-32][i] << (32-this->getHeight());
	}
	return i;
}

