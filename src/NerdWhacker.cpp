
#include "NerdWhacker.h"



NerdWhacker::NerdWhacker() {

    // GENERAL
    ofSetFrameRate(NUM_FRAMES);
    ofSetWindowTitle("NerdWhacker");
	ofSetVerticalSync(true);

    // ARDUINO
    //serial.enumerateDevices();
    serial.setup(0, 115200); //"/dev/tty.usbserial-A4001JEC"

    // MAPPING
    #ifdef USESYPHON
        syphon.setName("NERDWHACKER");
    #endif


    // GAME
    game = new Game();
}



void NerdWhacker::update() {

    // ARDUINO-WRITE

    countCycles++;
    if (countCycles==24) {

        // score_1 + score_2 + score_3
        int score = game->score;
        string score_string = "";
        if (score<100) score_string += "0";
        if (score<10) score_string += "0";
        score_string += ofToString(score);
        const char * score_chars = score_string.c_str();
        char s1 = score_chars[0];
        char s2 = score_chars[1];
        char s3 = score_chars[2];

        // lives
        int lives = game->lives;
        string lives_string = "";
        if (lives<10) lives_string += "0";
        lives_string += ofToString(lives);
        const char * lives_chars = lives_string.c_str();
        char l1 = lives_chars[0];
        char l2 = lives_chars[1];

        /*
        // ranking_1 + ranking_2 + ranking_3
        int ranking = game->rank + 1;
        string ranking_string = "";
        if (ranking<100) ranking_string += "0";
        if (ranking<10) ranking_string += "0";
        ranking_string += ofToString(ranking);
        const char * ranking_chars = ranking_string.c_str();
        char r1 = ranking_chars[0];
        char r2 = ranking_chars[1];
        char r3 = ranking_chars[2];
        */

        // topscore_1 + topscore_2 + topscore_3
        int topscore = game->topscore;
        string topscore_string = "";
        if (topscore<100) topscore_string += "0";
        if (topscore<10) topscore_string += "0";
        topscore_string += ofToString(topscore);
        const char * topscore_chars = topscore_string.c_str();
        char t1 = topscore_chars[0];
        char t2 = topscore_chars[1];
        char t3 = topscore_chars[2];

        // send string

        // vervangen door score_string!?
        unsigned char buf[NUM_BYTES_OUT] = {s1, s2, s3, l1, l2, t1, t2, t3};
        serial.writeBytes(&buf[0], NUM_BYTES_OUT);

        countCycles = 0;
    }

    // ARDUINO-READ

    unsigned char bytesReturned[NUM_BYTES_IN];
    memset(bytesReturned, 0, NUM_BYTES_IN);

    while (serial.readBytes(bytesReturned, NUM_BYTES_IN) > 0){}

    string plx = ofToString(bytesReturned);
    if (plx.length()>0) {
        cout << "input: " << plx << endl;

        /*
        if (plx=="a") hammerTime(0);
        else if (plx=="b") hammerTime(1);
        else if (plx=="i") hammerTime(2);
        else if (plx=="l") hammerTime(3);
        else if (plx=="c") hammerTime(4);
        else if (plx=="e") hammerTime(5);
        else if (plx=="d") hammerTime(6);
        else if (plx=="j") hammerTime(7);
        else if (plx=="h") hammerTime(8);
        else if (plx=="f") hammerTime(9);
        else if (plx=="g") hammerTime(10);
        else if (plx=="k") hammerTime(11);
         */
        if (plx=="a") hammerTime(0);
        else if (plx=="b") hammerTime(1);
        else if (plx=="c") hammerTime(4);
        else if (plx=="d") hammerTime(5);
        else if (plx=="e") hammerTime(10);
        else if (plx=="f") hammerTime(8);
        else if (plx=="g") hammerTime(6);
        else if (plx=="h") hammerTime(9);
        else if (plx=="i") hammerTime(2);
        else if (plx=="j") hammerTime(11);
        else if (plx=="k") hammerTime(7);
        else if (plx=="l") hammerTime(3);

    }

    game->update();
}



void NerdWhacker::draw() {

    /*SYPHON*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game->draw();
    #ifdef USESYPHON
        syphon.publishScreen();
    #endif

}



void NerdWhacker::keyReleased(int key) {

    switch (key) {
        case 112: // p = (re)play
            game->start();
            break;
        case 97: // a = plexi 1
            hammerTime(0);
            break;
        case 122: // z = plexi 2
            hammerTime(1);
            break;
        case 101: // e = plexi 3
            hammerTime(2);
            break;
        case 114: // r = plexi 4
            hammerTime(3);
            break;
        case 113: // q = plexi 5
            hammerTime(4);
            break;
        case 115: // s = plexi 6
            hammerTime(5);
            break;
        case 100: // d = plexi 7
            hammerTime(6);
            break;
        case 102: // f = plexi 8
            hammerTime(7);
            break;
        case 119: // w = plexi 9
            hammerTime(8);
            break;
        case 120: // x = plexi 10
            hammerTime(9);
            break;
        case 99: // c = plexi 11
            hammerTime(10);
            break;
        case 118: // v = plexi 12
            hammerTime(11);
            break;
    }
}



void NerdWhacker::hammerTime(int v) {
    if (!game->countdown && !game->playing) {
        game->start();
    }
    game->p[v]->hit();
}


