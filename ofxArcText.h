#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofxArcText : public ofxTrueTypeFontUC {
public:

    ofxArcText();
    
    void drawString(string s, float x, float y, float radius, bool asShapes=false);
    void drawStringAsShapes(string s, float x, float y, float radius);
    float getCharacterWidth(char ch);
    int getLength(string s); //corrected for 3 bytes UTF-8 characters
    string getChar(string s, int pos);

    enum { LEFT, CENTER, RIGHT } align;
    bool showDebug;
};
