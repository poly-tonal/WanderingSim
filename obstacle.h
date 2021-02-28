#pragma once
#include "ofMain.h"
class obstacle
{
public:
	//object functions
	void setup(float x, float y, float r);
	void draw();

	//variables
	float x, y, r;
	float pix = 5;
};

