#pragma once
#include "ofMain.h"
#include "obstacle.h"
class person
{
public:
	//object functions
	void setup(float x, float y, ofColor color); //create blobs
	void run(person people[]); //physics interactions
	void run(); //overload for testing without full array
	void applyForce(ofVec2f force);
	void update();
	void draw();
	void avoid(person p);
	void edges(); //avoid walls
	void changes(float _r, float _maxSpeed, float _maxForce, bool show); //allow updates from ofxGui
	void obst(obstacle o); //avoid obsticles

	ofVec2f pos, vel, acc; //vectors for position, velocity, and acceleration
	float r, maxForce, maxSpeed; //parameters 
	ofColor color; //colour creation for different blobs
	bool bShow = true; //switch for velocity/force display
};

