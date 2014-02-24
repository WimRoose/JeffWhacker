
#ifndef PLEXI
#define PLEXI



#import "ofMain.h"
#include <iostream>



class Plexi {
    
public:
    
    Plexi(int x, int y);
    void update();
    void draw();
    
    void init();
    void light(string p, int v, int s);
    void hit();
    void died();
    void reset();
    
    int value;
    //int score;
    
    bool isHit;
    bool isLit;
    bool isDead;
    
    ofImage image;
    
private:
    
    int x;
    int y;
    
    float hit_ts;
    float lit_ts;
    float dead_ts;
    
    bool isMatch;
    
};



#endif


