#include "obstacle.h"

void obstacle::setup(float _x, float _y, float _r) {
	//set local values from object input
	x = _x;
	y = _y;
	r = _r;
}

void obstacle::draw() {
	//draw obstacle as white circle at x, y with radius r
	ofSetColor(255);
	ofFill();
	ofDrawCircle(x, y, r);
	//draw black circle inside white circle with radius of r - pix
	//to have visual difference to person objects
	ofSetColor(0);
	ofFill();
	ofDrawCircle(x, y, r - pix);
}