#ifndef DRAGGABLE_H
#define DRAGGABLE_H
#include <ofxXmlSettings.h>

class Draggable
{
    public:
        Draggable();
        virtual ~Draggable();
    protected:
    private:
        ofxXmlSettings settings;
};

#endif // DRAGGABLE_H
