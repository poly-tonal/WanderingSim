#include "person.h"


void person::setup(float x, float y, ofColor _color) {
	acc = ofVec2f(0, 0); //set starting acceleration to 0
	float angle = ofRandom(360); //pick random angle
	vel = ofVec2f(cos(angle), sin(angle)); //create velocity vector in direction of angle
	pos = ofVec2f(x, y); //use input for starting position vector
	//set starting values
	r = 10; 
	maxSpeed = 2;
	maxForce = 0.03;
	color = _color;
}

void person::run(person people[]) {
	//call physics interactions
	update();
	edges();
	//add random noise to movement //simulate realistic wandering
	applyForce(ofVec2f(ofSignedNoise(pos.x, pos.y) * maxForce, ofSignedNoise(pos.x, pos.y) * maxForce));
	//check collisions with all other people in person array
	for (int i = 0; i < 4; i++) {
		avoid(people[i]);
	}
}

void person::run() {
	//single person version of run()
	update();
	edges();
	applyForce(ofVec2f(ofSignedNoise(pos.x, pos.y) * maxForce, ofSignedNoise(pos.x, pos.y) * maxForce));
}

void person::avoid(person p) {
	//person to person collision
	float dist = pos.distance(p.pos); //get distance between current person and member of array

	//check distance is greater than 0 to rule out self
	//check distance is less than 4 raddii so interactions are only in close proximity
	if (dist > 0 && dist < r * 4) {
		//get angle facing away from oncoming person
		float angle = atan2(pos.y - p.pos.y, pos.x - p.pos.x);
		//apply force along angle //force determined based on distance. closer = higher force
		applyForce(ofVec2f(ofMap(dist, 0, r * 4, 0.5, 0) * cos(angle), ofMap(dist, 0, r * 4, 0.5, 0) * sin(angle)));
	}
}

void person::applyForce(ofVec2f force) {
	//add force vector to acceleration vector
	acc += force;
}

void person::update() {
	//actually apply force
	vel += acc;
	//limit velocity to ensure no highspeed people
	vel.limit(maxSpeed);
	pos += vel;
	//reinitialise acceleration
	acc *= 0;
}

void person::draw() {
	//draw person to screen
	ofSetColor(color);
	ofDrawCircle(pos, r);
	//draw velocity/accelration lines
	if (bShow) {
		ofDrawLine(pos, pos + pow(r, 2) * vel);
	}
	else {
		ofDrawLine(pos, pos + pow(r, 2) * acc);
	}
}

void person::edges() {
	//check for proximity to edge of window,
	//apply force away from edge with random directional force perpendicular to edge for more natural curve
	if (pos.x < (r * 5)) applyForce(ofVec2f((maxForce * 3), ofRandom(-maxForce, maxForce)));
	if (pos.y < (r * 5)) applyForce(ofVec2f(ofRandom(-maxForce, maxForce), (maxForce * 3)));
	if (pos.x > ofGetWidth() + (-r * 5)) applyForce(ofVec2f(-(maxForce * 3), ofRandom(-maxForce, maxForce)));
	if (pos.y > ofGetHeight() + (-r * 5)) applyForce(ofVec2f(ofRandom(-maxForce, maxForce), -(maxForce * 3)));
}

void person::changes(float _r, float _maxSpeed, float _maxForce, bool showType) {
	//update person from gui values
	r = _r;
	maxSpeed = _maxSpeed;
	maxForce = _maxForce;
	bShow = showType;
}

void person::obst(obstacle o) {
	//collision for obstacles
	//find disance and angle from obstacle
	ofVec2f obst = ofVec2f(o.x, o.y);
	float dist = pos.distance(obst);
	if (dist < (o.r * 2 + 3 * r)) {
		float angle = atan2(pos.y - o.y, pos.x - o.x);
		//set velocity and acc to zero to ensure no crossover regardless of maxForce/maxSpeed
		vel.zero();
		acc.zero();
		//apply force along angle //force determined based on distance. closer = higher force
		applyForce(ofVec2f(ofMap(dist, 0, o.r + r * 3, 0.5, 0) * cos(angle), ofMap(dist, 0, o.r * 2 + r * 3, 0.5, 0) * sin(angle)));
	}
}