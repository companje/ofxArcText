openFrameworks addon for displaying an ofTrueType font on a circular path
created by Rick Companje for Globe4D - www.globe4d.com

Usage:

<pre>
#include "ofxArcText.h"
ofxArcText font;

setup:
  font.loadFont("vag.ttf",70);
  font.setLetterSpacing(1.1);
  font.align = font.CENTER;

draw:
  font.drawString("This text is curved with a 300px radius", ofGetWidth()/2, ofGetHeight()/2, 300);
</pre>
