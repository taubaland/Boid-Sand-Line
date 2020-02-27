#pragma once

#include "ofMain.h"
#include "Boid.h"
#include "ofxSandLine.h"

#define NBOIDS 50

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	Boid boid;
	std::vector<Boid> flock;

	ofxSandLine spline;
	ofPoint start;
	ofPoint end;
	
	bool pdfRendering;
	bool oneShot;

	ofImage img;
};
