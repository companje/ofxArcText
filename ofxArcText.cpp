#include "ofxArcText.h"

ofxArcText::ofxArcText() {
    align = CENTER;
    showDebug = false;
    antiAliasingScale = 2;
}

void ofxArcText::loadFont(string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt, int dpi) {
    //font is loaded twice as big as requested to perform a much better anti-aliasing
    ofTrueTypeFont::loadFont(filename, fontsize*antiAliasingScale, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
}

float ofxArcText::getCharacterWidth(char ch) {
    if (ch==' ') ch='.';
    return cps[ch-NUM_CHARACTER_TO_START].setWidth;
}

void ofxArcText::drawStringAsShapes(string text, float x, float y, float radius) {
    drawString(text,x,y,radius,true);
}

void ofxArcText::drawString(string text, float x, float y, float radius, bool asShapes) {
    ofPushMatrix();
    ofScale(1/antiAliasingScale,1/antiAliasingScale);
    ofTranslate(x,y);

    radius*=antiAliasingScale;
    x*=antiAliasingScale;
    y*=antiAliasingScale;

    float angles[text.length()];
    float widths[text.length()];
    float totalAngle = 0;

    for (int i=0; i<text.length(); i++) {
        widths[i] = getCharacterWidth(text.at(i)) * letterSpacing;
        angles[i] = atan(widths[i]/radius);
        totalAngle += angles[i];
    }

    switch (align) {
        case LEFT: break;
        case CENTER: ofRotateZ(ofRadToDeg(totalAngle/2)); break;
        case RIGHT: ofRotateZ(ofRadToDeg(totalAngle)); break;
    }

    //draw debug lines
    if (showDebug) {
        ofPushMatrix();
        ofPushStyle();
        ofNoFill();
        ofCircle(0,0,radius);
        ofSetColor(255,0,0);
        ofLine(0,0,0,radius);
        for (int i=1; i<=text.length(); i++) {
            ofRotateZ(-ofRadToDeg(angles[i-1]));
            if (i==text.length()) ofSetColor(0,0,255);
            else ofSetColor(0,200,0);
            ofLine(0,0,0,radius);
        }
        ofPopStyle();
        ofPopMatrix();
    }

    //draw letters
    ofPushMatrix();
    for (int i=0; i<text.length(); i++) {
        ofPushMatrix();
        ofTranslate(0, radius);
        ofRotateZ(-ofRadToDeg(angles[i])/2); //local rotation, use this or center letter before rotating
        string str = ofToString((unsigned char)text.at(i));
        if (asShapes) ofTrueTypeFont::drawStringAsShapes(str,0,0);
        else ofTrueTypeFont::drawString(str,0,0);
        ofPopMatrix();
        ofRotateZ(-ofRadToDeg(angles[i]));
    }
    ofPopMatrix(); //draw letters

    ofPopMatrix(); //drawString
}
