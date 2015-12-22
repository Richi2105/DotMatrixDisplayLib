//#include "include/DisplayCommunication.h"
#include "../include/DisplayCommunication.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
//#include "/usr/local/include/bcm2835.h"

#define DEBUG

const char COMMAND_INIT_GPIO_SPI[] = "gpio load spi";

DisplayCommunication * DisplayCommunication::singletonPointer = nullptr;

DisplayCommunication::DisplayCommunication(int xResolution, int yResolution)
{
    this->xResolution = xResolution;
    this->yResolution = yResolution;

    this->xPosition = 0;
    this->yPosition = 0;

    this->numberOfData = 0;

    this->transmitData[0] = 0;

#ifdef RASPBERRY
    system(COMMAND_INIT_GPIO_SPI);
    wiringPiSetupSys();

    this->fdSPI = wiringPiSPISetup(0, 500000);

/*	bcm2835 lib
    bcm2835_init(); //sudo?

    bcm2835_spi_begin();
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
*/
#endif //RASPBERRY_PI

//    DisplayCommunication::singletonPointer = this;
}

DisplayCommunication::~DisplayCommunication()
{
    DisplayCommunication::singletonPointer = nullptr;
}

void DisplayCommunication::initSingleton(int xResolution, int yResolution)
{
    if (DisplayCommunication::singletonPointer == nullptr)
    {
        DisplayCommunication::singletonPointer = new DisplayCommunication(xResolution, yResolution);
//        cout << "singleton class already in use\n";
    }
    else
    {

    }

}

DisplayCommunication * DisplayCommunication::getSingleton()
{
    return DisplayCommunication::singletonPointer;
}

void DisplayCommunication::clearDisplay()
{
    printf("clearing Display...\n");
    for(int j=0; j<this->yResolution/8; j+=1)
    {
        this->setPosition(0, j*8, true);

        this->numberOfData = 0;
        this->transmitData[numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_CS1 + this->DISPLAY_CS2;
        this->transmitData[numberOfData++] = this->xResolution/2;
        for (int i=0; i<this->xResolution/2; i+=1)
        {
            this->transmitData[numberOfData++] = 0;
        }
        this->transmit();
    }
}

void DisplayCommunication::transmit()
{
#ifdef DEBUG
    int i;
    for (i=0; i<this->numberOfData; i++)
    {
        printf("%2x ", transmitData[i]);
    }
    printf("\n");
#endif //DEBUG

#ifdef RASPBERRY
    wiringPiSPIDataRW(0, transmitData, numberOfData);
    //bcm2835_spi_writenb(transmitData, numberOfData);
#endif //RASPBERRY_PI
    //sleep(2);

}

void DisplayCommunication::setPosition(int xPos, int yPos, bool bothSides)
{
    this->numberOfData = 0;
    if (bothSides)
    {
    	this->transmitData[this->numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_A0 + this->DISPLAY_CS1 + this->DISPLAY_CS2;
    }
    else
    {
		if (xPos >= this->xResolution/2)
		{
			this->transmitData[this->numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_A0 + this->DISPLAY_CS2;
		}
		else
		{
			this->transmitData[this->numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_A0 + this->DISPLAY_CS1;
		}
    }
    this->transmitData[this->numberOfData++] = 2;
    this->transmitData[this->numberOfData++] = this->COMMAND_DISPLAY_START_COLUMN + (xPos % (this->xResolution/2));
    this->transmitData[this->numberOfData++] = this->COMMAND_DISPLAY_START_PAGE + (yPos / 8);
    this->transmit();
}

int DisplayCommunication::fillTransmitBuffer(int numOfBytes, uint8_t * data)
{
    int readPosition = 0;
    while (this->xPosition < this->xResolution/2)
    {
        this->transmitData[this->numberOfData++] = (uint8_t) *(data + readPosition);
        readPosition += 1;
        this->xPosition += 1;
        if (readPosition >= numOfBytes)
            break;
    }
    return readPosition;
}

void DisplayCommunication::sendToDisplay(int xPos, int yPos, int numOfBytes, uint8_t * data)
{
    int readPosition = 0;
    this->setPosition(xPos, yPos, false);
    this->numberOfData = 0;
    this->xPosition = xPos % (xResolution/2);
    if (xPos >= this->xResolution/2)
    {
        this->transmitData[this->numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_CS2;
        //Chipselect 2
    }
    else
    {
        this->transmitData[this->numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_CS1;
        //Chipselect 1
    }
    this->numberOfData += 1; //second byte tells number of transmit byte

    readPosition = this->fillTransmitBuffer(numOfBytes, data);

    this->transmitData[1] = this->numberOfData-2;
    this->transmit();

    this->numberOfData = 0;
    if (readPosition < numOfBytes)
    {
        if (this->xPosition < this->xResolution)
        {
            this->xPosition = 0;
            this->setPosition(this->xResolution/2, yPos, false);
            this->numberOfData = 0;
            this->transmitData[this->numberOfData++] = this->DISPLAY_START_COMMAND + this->DISPLAY_CS2;

            this->numberOfData += 1; //second byte tells number of transmit byte

            this->fillTransmitBuffer(numOfBytes-readPosition, data+readPosition);

            this->transmitData[1] = this->numberOfData-2;
            this->transmit();
        }
    }
}



