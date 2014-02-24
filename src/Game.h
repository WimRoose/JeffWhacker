
#ifndef GAME
#define GAME



#import "ofMain.h"
#include <iostream>
#include "Plexi.h"

#define SIZE 12
#define COUNTDOWN_TIME 4



class Game {

public:

    Game();
    void update();
    void draw();

    void init();
    void start();

    Plexi* p[SIZE];

    bool playing;
    bool countdown;

    int score;
    int lives;
    int rank;
    int topscore;

    vector<int> ranking;

private:

    float countdown_ts;

    string image[10];
    int value[10];
    string sounds[6];

    float speed;

    bool exit;

    ofSoundPlayer sound;

};



#endif
