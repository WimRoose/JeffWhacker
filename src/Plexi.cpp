
#include "Plexi.h"



Plexi::Plexi(int _x, int _y) {
    x = _x;
    y = _y;
    
    init();
}



void Plexi::init() {
    isLit = false;
    isHit = false;
    isMatch = false;
    isDead = false;
}



void Plexi::light(string p, int v, int s) {
    image.loadImage(p);
    value = v;
    
    isLit = true;
    lit_ts = ofGetElapsedTimeMillis() + s;
}



void Plexi::hit() {
    isHit = true;
    hit_ts = ofGetElapsedTimeMillis() + 100;
}


void Plexi::died() {
    image.loadImage("supernerd.jpg");
    isDead = true;
    dead_ts = ofGetElapsedTimeMillis() + 1000;
}



void Plexi::reset() {
    value = 0;
    image.clear();
}



void Plexi::update() {
    
    if (isLit && ofGetElapsedTimeMillis() > lit_ts) {
        isLit = false;
        image.clear();
    }
    
    if (isDead && ofGetElapsedTimeMillis() > dead_ts) {
        isDead = false;
        image.clear();
    }
    
    if (isHit && ofGetElapsedTimeMillis() > hit_ts) isHit = false;
}



void Plexi::draw() {
    
    if (isHit) { // yellow
        ofSetColor(255, 255, 0);
        ofRect(x, y, 150, 150);
    }
    else if (image.isAllocated()) { // 3-2-1-image
        ofSetColor(255, 255, 255);
        image.draw(x, y, 150, 150);
    }
    else {
        ofSetColor(46, 49, 146); // blue
        ofRect(x, y, 150, 150);
    }
}


