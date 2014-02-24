
#include "Game.h"
#include "Draggable.h"


Game::Game() {

    Draggable d;
    p[0] = new Plexi(25, 25);
    p[1] = new Plexi(225, 25);
    p[2] = new Plexi(425, 25);
    p[3] = new Plexi(625, 25);
    p[4] = new Plexi(25, 225);
    p[5] = new Plexi(225, 225);
    p[6] = new Plexi(425, 225);
    p[7] = new Plexi(625, 225);
    p[8] = new Plexi(25, 425);
    p[9] = new Plexi(225, 425);
    p[10] = new Plexi(425, 425);
    p[11] = new Plexi(625, 425);

    image[0] = "tiger.gif";
    value[0] = 1;
    image[1] = "monkey.gif";
    value[1] = 1;
    image[2] = "elephant.gif";
    value[2] = 1;
    image[3] = "bird.gif";
    value[3] = 1;
    image[4] = "snake.gif";
    value[4] = 1;
    image[5] = "supernerd.jpg";
    value[5] = -1;

    sounds[0] = "lefthook.mp3";
    sounds[1] = "punch.mp3";
    sounds[2] = "rightcross.mp3";
    sounds[3] = "slap.mp3";
    sounds[4] = "righthook.mp3";
    sounds[5] = "uppercut.mp3";

    ranking.clear();

    countdown = false;
    playing = false;
    score = 0;
    topscore = 0;
    lives = 12;
}



void Game::start() {

    if (score > 0) {
        ranking.push_back(score);
    }

    for (int i=0; i<SIZE; i++) {
        p[i]->init();
    }

    playing = false;
    speed = 1000;
    score = 0;
    lives = 12;
    rank = ranking.size();

    countdown = true;
    countdown_ts = ofGetElapsedTimef() + COUNTDOWN_TIME;
}



void Game::update() {

    rank = 0;
    for (int i=0; i<ranking.size(); i++) {
        if (score < ranking[i]) rank++;
    }

    //cout << "score=" << score << " topscore=" << topscore << " rank=" << rank+1 << endl;

    if (countdown) {
        int countdown_rest = floor(countdown_ts - ofGetElapsedTimef());
        //cout << "countdown: " << ofToString(countdown_rest) << endl;

        if (countdown_rest > 0) {
            string img;
            switch (countdown_rest) {
                case 3: img = "three"; break;
                case 2: img = "two"; break;
                case 1: img = "one"; break;
            }
            for (int i=0; i<SIZE; i++) {
                p[i]->image.loadImage(img+".gif");
            }
            if (!sound.getIsPlaying()) {
                sound.loadSound(img+".wav");
                sound.play();
            }
        }

        if (countdown_rest<=0) {
            for (int i=0; i<SIZE; i++) {
                p[i]->image.clear();
            }

            countdown = false;
            playing = true;
        }
    }
    else if (playing) {

        // check if plexi is lit
        bool active = false;
        bool dead = false;

        for (int i=0; i<SIZE; i++) {

            if (p[i]->isLit) {
                active = true;

                if (p[i]->isHit) {

                    if (p[i]->value > 0) {
                        score += p[i]->value;
                        if (score>topscore) topscore = score;
                        p[i]->value = 0;
                        p[i]->image.clear();
                        if (speed>1) speed -= 2;

                        if (lives<=4) lives = 4;
                        else if (lives<=8) lives = 8;
                        else lives = 12;

                        int r = ofRandom(6);
                        sound.loadSound(sounds[r]);
                        sound.play();
                    }

                    if (p[i]->value < 0) {
                        if (lives<=4) lives = 0;
                        else if (lives<=8) lives = 4;
                        else lives = 8;

                        p[i]->value = 0;

                        if (lives==0) {
                            playing = false;
                            dead = true;

                            sound.loadSound("dead.wav");
                            sound.play();
                        }
                        else {
                            sound.loadSound("bomb.wav");
                            sound.play();
                        }
                    }
                }
            }

            p[i]->update();
        }

        if (dead) {
            for (int i=0; i<SIZE; i++) {
                p[i]->died();
            }
        }
        else if (!active) {
            lives--;
            if (lives==0) {
                playing = false;
                dead = true;
            }

            int r = ofRandom(6);
            p[int(ofRandom(SIZE))]->light(image[r], value[r], speed);
        }

        //cout << ofToString(score) << " | " << ofToString(lives) << " | " << ofToString(speed) << endl;
    }
    else {

        for (int i=0; i<SIZE; i++) {
            p[i]->update();
        }

        if (!p[0]->isDead) {
            int r = ofRandom(6);
            p[int(ofRandom(SIZE))]->light(image[r], value[r], 500);
        }
    }
}



void Game::draw() {

    for (int i=0; i<SIZE; i++) {
        p[i]->draw();
    }
}


