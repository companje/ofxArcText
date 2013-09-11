#include "ofxArcText.h"

#include "Poco/UTF8Encoding.h"
#include "Poco/Latin9Encoding.h"
#include "Poco/TextConverter.h"

ofxArcText::ofxArcText() {
    align = CENTER;
    antiAliasingScale = 2;
}

void ofxArcText::loadFont(string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt, int dpi, int antiAliasingScale) {
    //font is loaded 'antiAliasingScale times' as big as requested to get a much better anti-aliasing
    this->antiAliasingScale = antiAliasingScale;
    ofTrueTypeFont::loadFont(filename, fontsize*antiAliasingScale, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
}

void ofxArcText::drawString(string text, float x, float y, float radius, bool asShapes) {
    ofPushMatrix();
    ofTranslate(x,y);
    ofScale(1/antiAliasingScale,1/antiAliasingScale);
    radius*=antiAliasingScale;

    if (hasFullCharacterSet() && getEncoding()==OF_ENCODING_UTF8) {
		string o;
		Poco::TextConverter(Poco::UTF8Encoding(),Poco::Latin9Encoding()).convert(text,o);
		text=o;
	}

    bind();
    ofMesh &mesh = getStringMesh(text,0,0);

    float angle = 0;
    float px=0;

    for (int i=0; i<mesh.getNumVertices(); i+=4) {
        ofVec3f &a = mesh.getVertices().at(i+0);
        ofVec3f &b = mesh.getVertices().at(i+1);
        ofVec3f &c = mesh.getVertices().at(i+2);
        ofVec3f &d = mesh.getVertices().at(i+3);

        float x = b.x;
        float w = x-px;
        angle += atan(w/radius);
        px = x;

        translate(a,b,c,d,ofVec3f(-b.x,0,0));
        translate(a,b,c,d,ofVec3f(0,radius,0));
        rotate(a,b,c,d,-ofRadToDeg(angle),ofVec3f(0,0,1));
    }

    switch (align) {
        case LEFT: break;
        case CENTER: ofRotateZ(ofRadToDeg(angle/2)); break;
        case RIGHT: ofRotateZ(ofRadToDeg(angle)); break;
    }

	mesh.draw();
	unbind();

    ofPopMatrix();
}

void ofxArcText::translate(ofVec3f &a, ofVec3f &b, ofVec3f &c, ofVec3f &d, ofVec3f v) {
    a+=v; b+=v; c+=v; d+=v;
}

void ofxArcText::rotate(ofVec3f &a, ofVec3f &b, ofVec3f &c, ofVec3f &d, float degrees, ofVec3f axis) {
    a.rotate(degrees,axis);
    b.rotate(degrees,axis);
    c.rotate(degrees,axis);
    d.rotate(degrees,axis);
}
