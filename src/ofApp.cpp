#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFullscreen(true);
	//initialise osc and gui
	osc.setup(HOST, PORT);
	gui.setup();
	//add person pbjects to array at random position with their set colour
	p[0].setup(ofRandom(50, ofGetWidth()-50), ofRandom(50, ofGetHeight()-50), ofColor(255, 255, 255)); //drum //white
	p[1].setup(ofRandom(50, ofGetWidth()-50), ofRandom(50, ofGetHeight()-50), ofColor(0, 255, 0)); //arp //green
	p[2].setup(ofRandom(50, ofGetWidth()-50), ofRandom(50, ofGetHeight()-50), ofColor(0, 0, 255)); //lead //blue
	p[3].setup(ofRandom(50, ofGetWidth()-50), ofRandom(50, ofGetHeight()-50), ofColor(255, 0, 0)); //bass //red
	//name, set default, set range for gui
	gui.add(r.set("radius", 10, 1, 20));
	gui.add(maxSpeed.set("Speed", 2, 0, 5));
	gui.add(maxForce.set("force", 0.03, 0, 0.1));
	gui.add(bShow.set("vel/acc", true));
	//obstacles
	if(bObst){
		//initialise structured obstacles
		if (!bRand) {
			for (int i = 0; i < 12; i++) {
				if (i < 6) {
					obst[i].setup(150 + 300 * (i % 6), ofGetHeight() / 3, 20);
				}
				else {
					obst[i].setup(150 + 300 * (i % 6), (ofGetHeight() / 3) * 2, 20);
				}
			}
		}
		//initiaslise random obstacles
		else {
			for (int i = 0; i < 12; i++) {
					obst[i].setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 20);}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	//loop for each person
	for (int i = 0; i < 4; i++) {
		//person physics
		p[i].run(p);
		for (int j = 0; j < 12; j++) {
			//obstacle interaction
			p[i].obst(obst[j]);
		}
		//update person based on gui
		p[i].changes(r, maxSpeed, maxForce, bShow);

		//OSC
		//create new message
		ofxOscMessage message;
		switch (i) {
		case 0: //drum message
			message.setAddress("/loop1");
			message.addFloatArg(ofMap(p[i].pos.x, 0, ofGetWidth(), 0.0f, 200.0f, true));
			message.addFloatArg(ofMap(p[i].pos.y, 0, ofGetHeight(), 1.0f, 0.0f, true));
			osc.sendMessage(message, false);
			break;
		case 1: //arp message
			message.setAddress("/loop2"); //MIDI notes set to sectors sent to pd to create chords
			if (p[i].pos.x < (ofGetWidth() / 4) && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(62);
			}
			else if (p[i].pos.x < (ofGetWidth() / 2) && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(67);
			}
			else if (p[i].pos.x < (ofGetWidth() / 4) * 3 && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(64);
			}
			else if (p[i].pos.x < ofGetWidth() && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(72);
			}
			else if (p[i].pos.x < (ofGetWidth() / 4) && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(65);
			}
			else if (p[i].pos.x < (ofGetWidth() / 2) && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(60);
			}
			else if (p[i].pos.x < (ofGetWidth() / 4) * 3 && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(69);
			}
			else if (p[i].pos.x < ofGetWidth() && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(71);
			}
			osc.sendMessage(message, false);
			break;
		case 2: //lead message
			message.setAddress("/loop3");
			message.addFloatArg(ofMap(p[i].pos.x, 0, ofGetWidth(), 60, 72, true)); //notes
			message.addFloatArg(ofMap(p[i].pos.y, 0, ofGetHeight(), 1.0f, 0.0f, true));  //reverb amount
			osc.sendMessage(message, false);
			break;
		case 3: //bass message
			message.setAddress("/loop4"); //MIDI notes set to sectors sent to pd
			if (p[i].pos.x < (ofGetWidth() / 4) && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(38);
			}
			else if (p[i].pos.x < (ofGetWidth() / 2) && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(43);
			}
			else if (p[i].pos.x < (ofGetWidth() / 4) * 3 && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(40);
			}
			else if (p[i].pos.x < ofGetWidth() && p[i].pos.y < (ofGetHeight() / 2)) {
				message.addFloatArg(48);
			}
			else if (p[i].pos.x < (ofGetWidth() / 4) && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(41);
			}
			else if (p[i].pos.x < (ofGetWidth() / 2) && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(36);
			}
			else if (p[i].pos.x < (ofGetWidth() / 4) * 3 && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(45);
			}
			else if (p[i].pos.x < ofGetWidth() && p[i].pos.y < ofGetHeight()) {
				message.addFloatArg(47);
			}
			message.addFloatArg(ofMap(p[i].pos.y, 0, ofGetHeight(), 1.0f, 0.0f, true));  //controls keyswap
			osc.sendMessage(message, false);
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//draw each aspect to screen
	ofBackground(0);
	for (int i = 0; i < 4; i++) {
		p[i].draw();
	}
	for (int i = 0; i < 12; i++) {
		obst[i].draw();
	}
	gui.draw();
}
