#include "Draggable.h"

Draggable::Draggable()
{
    settings.loadFile("settings.xml");
    int blinkRate = settings.getValue("settings:plexi_1:xdfhi", 0);
}

Draggable::~Draggable()
{
    //dtor
}
