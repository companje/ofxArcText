#pragma once

#include "ofMain.h"
#include "ofxArcText.h"

class testApp : public ofBaseApp {
public:
    void setup();
    void draw();
    void keyPressed(int key);

    string text;
    ofxArcText font;
};
