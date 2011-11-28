#include "ofxArcText.h"

ofxArcText::ofxArcText() {
    align = OFX_ALIGN_CENTER;
    radius = 1;
    text = "";
    color = ofColor::white;
    nTimes = 1;
    visible = true;
}

void ofxArcText::customDraw() { 
    float radius = this->radius / getScale().x; //local

    for (int i=0; i<nTimes; i++) {
        
        ofPushMatrix();
        ofRotateZ(360/nTimes*i);

        switch (align) {
            case OFX_ALIGN_LEFT: ofRotateZ(0); break;
            case OFX_ALIGN_CENTER: ofRotateZ(ofRadToDeg(atan((stringWidth(text)/2) / radius))); break;
            case OFX_ALIGN_RIGHT: ofRotateZ(2*ofRadToDeg(atan((stringWidth(text)/2) / radius))); break;
        }

        for (int i=0; i<text.length(); i++) {
            char ch = text.at(i)==' ' ? 'i' : text.at(i);
            float opposite = cps[ch-NUM_CHARACTER_TO_START].setWidth / 2;
            ofRotateZ(-ofRadToDeg(atan(opposite/radius)));
            ofSetColor(color);
            drawString(ofxToString(text.at(i)),-opposite,radius);
            ofRotateZ(-ofRadToDeg(atan(opposite/radius)));
        }
        
        ofPopMatrix();
    }
}
