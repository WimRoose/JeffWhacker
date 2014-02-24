
#ifndef NERDWHACKER
#define NERDWHACKER


#ifdef USESYPHON
    #include "ofxSyphon.h"
#endif

#include <iostream>

#include "ofMain.h"
#include "Game.h"

#define NUM_BYTES_IN 3
#define NUM_BYTES_OUT 10
#define NUM_FRAMES 24



class NerdWhacker : public ofBaseApp {

public:
    NerdWhacker();
    void update();
    void draw();

    void keyReleased(int key);
    void hammerTime(int v);

    // GAME
    Game* game;

    // ARDUINO
    ofSerial serial;

    // MAPPING
    #ifdef USESYPHON
        ofxSyphonServer syphon;
    #endif


private:
    int countCycles;
};



#endif
