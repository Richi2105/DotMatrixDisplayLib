#ifndef DISPLAYCOMMUNICATION_H
#define DISPLAYCOMMUNICATION_H

#include <cstdint>


class DisplayCommunication
{
    public:
        ~DisplayCommunication();

        void sendToDisplay(int xPos, int yPos, int numOfBytes, uint8_t * data);

        static DisplayCommunication * getSingleton();
        static void initSingleton(int xResolution, int yResolution);

        void clearDisplay();

        int getXResolution();
        int getYResolution();

        int getCurrentXPositon();

        static const uint8_t DISPLAY_START_COMMAND = 0xC0;
        static const uint8_t DISPLAY_CS1 = 0x01;
        static const uint8_t DISPLAY_CS2 = 0x02;
        static const uint8_t DISPLAY_A0 = 0x08;

        static const uint8_t COMMAND_DISPLAY_ON = 0xAF;
        static const uint8_t COMMAND_DISPLAY_OFF = 0xAE;
        static const uint8_t COMMAND_DISPLAY_STATIC_DRIVE_ON = 0xA5;
        static const uint8_t COMMAND_DISPLAY_STATIC_DRIVE_OFF = 0xA4;

        static const uint8_t COMMAND_DISPLAY_START_LINE = 0xC0;
        static const uint8_t COMMAND_DISPLAY_START_COLUMN = 0x00;
        static const uint8_t COMMAND_DISPLAY_START_PAGE = 0xB8;

        static const uint8_t COMMAND_DISPLAY_INCREMENT_CLOCKWISE = 0xA0;
        static const uint8_t COMMAND_DISPLAY_INCREMENT_COUNTERCLOCKWISE = 0xA1;

        static const uint8_t COMMAND_DISPLAY_RESET = 0xE2;
    protected:
    private:
        DisplayCommunication(int xResolution, int yResolution);
        void setPosition(int xPosition, int yPosition, bool bothSides);
        void transmit();
        int fillTransmitBuffer(int numOfBytes, uint8_t * data);

        static DisplayCommunication * singletonPointer;

        int xResolution;
        int yResolution;

        int xPosition;
        int yPosition;

        unsigned char transmitData[150];
        int numberOfData;

        int fdSPI;
};

#endif // DISPLAYCOMMUNICATION_H
