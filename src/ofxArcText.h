#pragma once
#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofxArcText {
public:
    enum Alignment { LEFT, CENTER, RIGHT };
    void drawString(ofxTrueTypeFontUC &font, string s, float radius, Alignment align=CENTER, int nCopies=1);

private:
    void translate(ofVec3f &a, ofVec3f &b, ofVec3f &c, ofVec3f &d, ofVec3f v);
    void rotate(ofVec3f &a, ofVec3f &b, ofVec3f &c, ofVec3f &d, float degrees, ofVec3f axis);
};
