#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1280, 720, OF_WINDOW); //create window //overwritten by ofSetFullscreen in ofApp.cpp
	ofRunApp(new ofApp()); //run app
}
