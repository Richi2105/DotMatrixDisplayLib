#ifndef DISPLAYPOSITION_H
#define DISPLAYPOSITION_H

//#include <Serializeable.h>
#include "/home/richard/workspace/EventSystemLib/include/Serializeable.h"


class DisplayPosition : public Serializeable
{
    public:
        DisplayPosition(int x, int y);
        DisplayPosition();
        virtual ~DisplayPosition();
        int getXPosition();
        int getYPosition();

        void setXPosition(int xpos);
        void setYPosition(int ypos);

        virtual int16_t getSerializedSize();
    	virtual int serialize(void* const data);
    	virtual int deserialize(void const * const data);

    protected:
    private:
        int xPosition;
        int yPosition;
};

#endif // DISPLAYPOSITION_H
