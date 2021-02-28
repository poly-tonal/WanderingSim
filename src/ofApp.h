#pragma once

//include external libraries for gui and OSC
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
//include object class files
#include "..\person.h"
#include "..\obstacle.h"

//deine OSC port and host
#define PORT 9001
#define HOST "localhost"

class ofApp : public ofBaseApp {

public:
	//ofApp functions
	void setup();
	void update();
	void draw();
	
	//create gui and gui elements
	ofxPanel gui;
	ofParameter<float> r, maxSpeed, maxForce;
	ofParameter<bool> bShow;

	//create OSC instance
	ofxOscSender osc;
	//create arrays of person and obstacle objects
	person p[4];
	obstacle obst[12];
	//create bool for obstales and randomness
	bool bObst = true;
	bool bRand = false;
};
