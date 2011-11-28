#pragma once

#include "ofxExtras.h"

class ofxArcText : public ofNode, public ofTrueTypeFont {
public:

    ofxArcText();
    void customDraw();
    
    float radius;
    int align;
    int nTimes;
    bool visible;
    
    string text;    
    ofColor color;

    vector<string> textValues;
    vector<string> colorValues;
};
