#pragma once
#include "ofMain.h"

class ofxArcText : public ofTrueTypeFont {
public:

    ofxArcText();

    void loadFont(string filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=false, bool makeContours=false, float simplifyAmt=0.3, int dpi=0, int antiAliasingScale=2);
    void drawString(string s, float x, float y, float radius, bool asShapes=false);

    enum { LEFT, CENTER, RIGHT } align;
    float antiAliasingScale;

private:
    void translate(ofVec3f &a, ofVec3f &b, ofVec3f &c, ofVec3f &d, ofVec3f v);
    void rotate(ofVec3f &a, ofVec3f &b, ofVec3f &c, ofVec3f &d, float degrees, ofVec3f axis);
};
