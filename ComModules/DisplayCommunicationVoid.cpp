//#include "include/DisplayCommunication.h"
#include "DisplayCommunicationVoid.h"

#define DEBUG

namespace DotMatrix
{

DisplayCommunicationVoid::DisplayCommunicationVoid(int xResolution, int yResolution)
{
	this->xResolution = xResolution;
	this->yResolution = yResolution;
}

DisplayCommunicationVoid::~DisplayCommunicationVoid()
{
}


void DisplayCommunicationVoid::sendToDisplay(int xPos, int yPos, int numOfBytes, unsigned char* data, bool inverted)
{

}

} /* namespace DotMatrix */


