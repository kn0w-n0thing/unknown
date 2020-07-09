#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	/*
	ofGLFWWindowSettings settings;

	settings.resizable = false;
	settings.decorated = false;
	settings.setPosition(ofVec2f(0,0));
	settings.setSize(1080, 1920);
	//settings.monitor = 1;

	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofApp> mainApp(new ofApp);

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
	*/
	
	ofSetupOpenGL(1080, 1920,OF_FULLSCREEN);			
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	

}
