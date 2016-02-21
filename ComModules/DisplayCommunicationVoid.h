#ifndef DISPLAYCOMMUNICATION_H
#define DISPLAYCOMMUNICATION_H

#include "DisplayCommunication.h"

namespace DotMatrix
{

class DisplayCommunicationVoid : public DisplayCommunication
{
    public:
        virtual ~DisplayCommunicationVoid();
        DisplayCommunicationVoid(int xResolution, int yResolution);

        virtual void sendToDisplay(int xPos, int yPos, int numOfBytes, unsigned char* data, bool inverted);

        virtual void display(DisplayList* list);
        virtual void display(DisplayString* string);

    protected:
    private:
//      int xResolution;
//      int yResolution;

};

} /* namespace DotMatrix */
#endif // DISPLAYCOMMUNICATION_H
