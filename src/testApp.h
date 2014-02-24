#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#ifdef USESYPHON
        #include "ofxSyphon.h"
#endif


class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	float 	counter;
	bool	bSmooth;

    ofTexture tex;
    #ifdef USESYPHON
        ofxSyphonServer mainOutputSyphonServer;
        ofxSyphonServer individualTextureSyphonServer;
        ofxSyphonClient mClient;
    #endif

};

#endif

