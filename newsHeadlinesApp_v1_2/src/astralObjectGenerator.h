#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class astralObjectGenerator {
    
    public:
       	
       	void init(string path);
       	void setupObject(float size, float rx, float ry);
       	void updateObject(float size, int camDist);
       	void loadTexture(string path);
       	void drawObject(string mode);
        string generateChineseText(ofJson emoObj);
        string generateEnglishText(ofJson emoObj);

    private:

		ofImage tex;
		ofMaterial material;
		ofxAssimpModelLoader model;
		ofLight directionalLight1, directionalLight2;
		ofEasyCam cam;
		float camOrbitX, camOrbitY, camOrbitZ;   
		float rotDegsX, rotDegsY; 

    ofJson dict;

};