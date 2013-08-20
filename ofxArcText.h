#pragma once

#include "ofMain.h"

class ofxArcText : public ofTrueTypeFont {
public:

    ofxArcText();
    
    void loadFont(string filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=false, bool makeContours=false, float simplifyAmt=0.3, int dpi=0);

    void drawString(string s, float x, float y, float radius, bool asShapes=false);
    void drawStringAsShapes(string s, float x, float y, float radius);
    float getCharacterWidth(char ch);

    enum { LEFT, CENTER, RIGHT } align;
    bool showDebug;
    float antiAliasingScale;
};
