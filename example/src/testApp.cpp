#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(0);
    
    font.loadFont("vag.ttf",70);
    font.setLetterSpacing(1.1);
    font.align = font.CENTER;
    
    text = "openFrameworks";
    ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void testApp::draw() {
    font.drawString(text, ofGetWidth()/2, ofGetHeight()/2, 300);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    if (key==OF_KEY_BACKSPACE && text.length()>0) text.erase(text.end()-1);
    else if (key>=32 && key<127) text += ofToString((char)key);
}
