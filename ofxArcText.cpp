#include "ofxArcText.h"

ofxArcText::ofxArcText() {
    align = CENTER;
    showDebug = false;
}

float ofxArcText::getCharacterWidth(char ch) {
    return stringWidth(ofToString(ch==' '?'p':ch));
    //return cps[ch-NUM_CHARACTER_TO_START].setWidth;
}

void ofxArcText::drawStringAsShapes(string text, float x, float y, float radius) {
    drawString(text,x,y,radius,true);
}

int ofxArcText::getLength(string s) { //corrected for 3 bytes UTF-8 characters
    //count the number of special chars (3 bytes) in the string
    int total = 0;
    for (int i=0; i<s.length(); i++) {
        if (s.at(i)<0) total++;
    }
    total/=3; //3 bytes per special char
    return s.length()-total*2; //subtract 2 of the length for each special char
}

string ofxArcText::getChar(string s, int pos) {
    string letter;
    int cur=0;
    
    for (int i=0; i<s.length(); i++) {
        letter += ofToString(s.at(i)); //add char to (multibyte) string 
        if (s.at(i)>0 || letter.size()>=3) {
            if (cur==pos) return letter;
            letter = "";
            cur++;
        }
    }
}

void ofxArcText::drawString(string text, float x, float y, float radius, bool asShapes) {
    ofPushMatrix();
    ofTranslate(x,y);
    
    float angles[text.length()];
    float widths[text.length()];
    float totalAngle = 0;
    
//    setLetterSpacing(1.1);
//    cout << letterSpacing << endl;
    
//    /letterSpacing * spaceSize
    
    for (int i=0; i<text.length(); i++) {
        string ch = getChar(text,i);
        widths[i] = stringWidth(ch==" " ? "p" : ch) * 1.2; //+ letterSpacing; //getCharacterWidth(text.at(i)) + letterSpacing;
        angles[i] = atan(widths[i]/radius);
        totalAngle += angles[i];
    }
    
    switch (align) {
        case LEFT: break;
        case CENTER: ofRotateZ(ofRadToDeg(totalAngle/2)); break;
        case RIGHT: ofRotateZ(ofRadToDeg(totalAngle)); break;
    }

    if (showDebug) {
        ofNoFill();
        ofCircle(0,0,radius);
        ofLine(0,0,0,radius);
        ofPushMatrix();
        for (int i=0; i<text.length(); i++) {
            ofRotateZ(-ofRadToDeg(angles[i]));
            ofLine(0,0,0,radius);
        }
        ofPopMatrix();
    }
    
    for (int i=0; i<text.length(); i++) {
        ofPushMatrix();
        ofTranslate(0, radius);
        ofRotateZ(-ofRadToDeg(angles[i])/2); //local rotation, use this or center letter before rotating
        if (asShapes) ofxTrueTypeFontUC::drawStringAsShapes(ofToString(getChar(text,i)),0,0);
        else ofxTrueTypeFontUC::drawString(ofToString(getChar(text,i)),0,0);
        ofPopMatrix();
        ofRotateZ(-ofRadToDeg(angles[i]));
    }

    ofPopMatrix();

    //for (int i=0; i<text.length(); i++) {
    //    float opposite = getCharacterWidth(text.at(i)) * letterSpacing;
    //    float angle = atan(opposite/radius) / 2;
    //    ofRotateZ(-ofRadToDeg(angle));
    //    string s = ofToString((char)text.at(i));
    //    ofTrueTypeFont::drawString(s,-widths[i]/2,radius);
    //    ofRotateZ(-ofRadToDeg(angle));
    //}
}
