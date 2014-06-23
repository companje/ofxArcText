#include "ofxArcText.h"

void ofxArcText::drawString(ofxTrueTypeFontUC &font, string s, float radius, Alignment align, int nCopies) {
  /// ofxArcText uses the ofxTrueTypeFontUC fork by companje:
  /// https://github.com/companje/ofxTrueTypeFontUC

  vector<unsigned int> charIDs = font.getCharacterIDs(s);
  vector<ofMesh> charMeshes = font.getCharacterQuads(s,0,0);

  if (charIDs.size()!=charMeshes.size()) {
    cout << "charIDs.size()!=charMeshes.size(): " << charIDs.size() << " vs " << charMeshes.size() << endl;
    std::exit(1);
  }

  float angle = 0;
  float px=0;

  for (int i=0; i<charIDs.size(); i++) {
    ofMesh &mesh = charMeshes.at(i);
    ofVec3f &a = mesh.getVertices().at(0);
    ofVec3f &b = mesh.getVertices().at(1);
    ofVec3f &c = mesh.getVertices().at(2);
    ofVec3f &d = mesh.getVertices().at(3);

    float x = b.x;
    float w = x-px;
    float z = i;
    angle += atan(w/radius);
    px = x;
  
    translate(a,b,c,d,ofVec3f(-b.x,0,z));
    translate(a,b,c,d,ofVec3f(0,radius,0));
    rotate(a,b,c,d,-ofRadToDeg(angle),ofVec3f(0,0,1));
  }

  switch (align) {
    case LEFT: break;
    case CENTER: ofRotateZ(ofRadToDeg(angle/2)); break;
    case RIGHT: ofRotateZ(ofRadToDeg(angle)); break;
  }

  for (int j=0; j<nCopies; j++) {
    ofPushMatrix();
    ofRotateZ(float(j)/nCopies*360);
    ofTranslate(0,0,j);
    
    for (int i=0; i<charIDs.size(); i++) {
      font.bind(charIDs.at(i));
      charMeshes.at(i).draw();
    }

    ofPopMatrix();
  }
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
