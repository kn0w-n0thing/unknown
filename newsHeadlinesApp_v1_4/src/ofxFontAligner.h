#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofxFontAligner {
    
    public:
       	
       	void init(string fontPath, float fontSize);
        void setFontSize(float fs);
        void setColor(ofColor c);
        ofVec2f drawLeft(string t, float x, float y, bool debug);
        ofVec2f drawCentered(string t, float x, float y, bool debug);
    	ofVec2f drawEnglishBlock(string t, float x, float y, float w, bool debug);
        ofVec2f drawChineseBlock(string t, float x, float y, float w, float rightMarginError, bool debug);
    	ofVec2f englishGraphicBlock(string t, float x, float y, float w, bool debug);
        ofVec2f chineseGraphicBlock(string t, float x, float y, float w, float rightMarginError, bool debug);
        ofVec2f getChineseBlockSize(string t, float x, float y, float w, float rightMarginError);
        ofVec2f getEnglishBlockSize(string t, float x, float y, float w);
        ofVec2f getSimpleBlockSize(string t);

    	ofxTrueTypeFontUC font;
    	string path;
    	float fSize;
    	float lHeight;
    	ofColor boundingBox, underlineColor, mainColor;
        ofVec2f boxSize;

    private:
        vector<string> chineseLines(string t, float w, bool wordCut, float rightMarginError);
    	vector<string> englishLines(string t, float w, bool wordCut);
};