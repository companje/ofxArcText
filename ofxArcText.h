#pragma once

#include "ofMain.h"

class ofxArcText : public ofTrueTypeFont {
public:

    ofxArcText();
    
    void drawString(string s, float x, float y, float radius, bool asShapes=false);
    void drawStringAsShapes(string s, float x, float y, float radius);
    float getCharacterWidth(char ch);

    enum { LEFT, CENTER, RIGHT } align;
    bool showDebug;
};
