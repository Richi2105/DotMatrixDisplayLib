#include "../DisplayObjects/DisplayString.h"

#include "../Fonts/Standard8mono.h"
#include <stdio.h>

namespace DotMatrix
{

//DisplayCommunication* DisplayString::communicationModule = nullptr;

DisplayString::DisplayString(DisplayPosition begin, DisplayPosition end, std::string str) : box(begin, end)
{
	memset(this->str, 0, DISPLAYSTRINGSIZE);
    memcpy(this->str, str.c_str(), DISPLAYSTRINGSIZE < str.size() ? DISPLAYSTRINGSIZE : str.size());
//    this->font = new Standard_8_mono();
    this->fontType = Font::standard_8_mono;
    this->inverted = false;
//    this->setCommunicationModule();
}

DisplayString::DisplayString(int x, int y, int length, std::string str)
{
	memset(this->str, 0, DISPLAYSTRINGSIZE);
    memcpy(this->str, str.c_str(), DISPLAYSTRINGSIZE < str.size() ? DISPLAYSTRINGSIZE : str.size());
//    this->font = new Standard_8_mono();
    this->fontType = Font::standard_8_mono;
    this->box = DisplayBoundary(x, y, x+length, y+Font::getFontHeight(this->fontType));
    this->inverted = false;
//    this->setCommunicationModule();
}

DisplayString::DisplayString() : box()
{
//    this->font = new Standard_8_mono();
    this->fontType = Font::standard_8_mono;
    this->inverted = false;
}

DisplayString::~DisplayString()
{
    //dtor
}
/*
void DisplayString::setCommunicationModule(DisplayCommunication* module)
{
    DisplayString::communicationModule = module;
}
*/
/*
void DisplayString::setCommunicationModule()
{
	if (DisplayString::communicationModule == nullptr)
	{
		DisplayString::communicationModule = DisplayCommunication::getSingleton();
	}
}
*/
DisplayPosition DisplayString::getPositionBegin()
{
    return this->box.getBegin();
}

DisplayPosition DisplayString::getPositionEnd()
{
    return this->box.getEnd();
}

void DisplayString::setPosition(DisplayPosition pos)
{
	int xdev, ydev;
	xdev = box.getXPosEnd() - box.getXPosBegin();
	ydev = box.getYPosEnd() - box.getYPosBegin();
    this->box.setNewBegin(pos);
    DisplayPosition posEnd(pos.getXPosition()+xdev, pos.getYPosition()+ydev);
    this->box.setNewEnd(posEnd);
}

std::string DisplayString::getString()
{
    return this->str;
}

void DisplayString::setString(std::string str)
{
	memset(this->str, 0, DISPLAYSTRINGSIZE);
    memcpy(this->str, str.c_str(), DISPLAYSTRINGSIZE < str.size() ? DISPLAYSTRINGSIZE : str.size());
}

void DisplayString::setFont(Font::font_t f)
{
	this->fontType = f;
/*	switch (f)
	{
case Font::standard_6: break;
case Font::standard_6_mono: break;
case Font::standard_8_mono: this->font = new Standard_8_mono();
default: break;
	}
*/
	//set new height:
	this->box.setYPosEnd(this->box.getYPosBegin() + Font::getFontHeight(this->fontType));
}

Font::font_t DisplayString::getFont()
{
	return this->fontType;
}

bool DisplayString::isInverted()
{
	return this->inverted;
}

void DisplayString::setInverted(bool invert)
{
	this->inverted = invert;
}

void DisplayString::display()
{
/*
    unsigned char data[122];
    int iterator = 0;
    int charPosition = 0;
    for (char c : str)
    {
        if (c > 31)
        {
            for (charPosition=0; charPosition<5; charPosition++)
            {
                data[iterator++] = TEXT_5x7[c-32][charPosition];
            }
            data[iterator++] = 0x00;
            if (iterator >= 120)
                break;
        }
    }
    DisplayString::communicationModule->sendToDisplay(this->box.getXPosBegin(), this->box.getYPosBegin(), iterator, data);
*/
	if (Displayable::dispCom != nullptr)
		Displayable::dispCom->display(this);
}

DisplayBoundary* DisplayString::getBoundary()
{
	return &this->box;
}

int DisplayString::getSerializedSize()
{
	int16_t size = 0;
	size += sizeof(char) * DISPLAYSTRINGSIZE;
	size += sizeof(this->inverted);
	size += sizeof(this->fontType);
	size += this->box.getSerializedSize();
	return size;
}
int DisplayString::serialize(void* const data)
{
	printf("DisplayString::serialize()\n");
	MEMUNIT* data2 = (MEMUNIT*)data;
	packNData(data2, this->str, DISPLAYSTRINGSIZE);
	packData(data2, this->inverted);
	packData(data2, this->fontType);
	data2 += this->box.serialize(data2);
	return this->getSerializedSize();
}

int DisplayString::deserialize(void const * const data)
{
	printf("DisplayString::deserialize()\n");
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackNData(data2, this->str, DISPLAYSTRINGSIZE);
	unpackData(data2, this->inverted);
	unpackData(data2, this->fontType);
	data2 += this->box.deserialize(data2);
	return this->getSerializedSize();
}

} /* namespace DotMatrix */
