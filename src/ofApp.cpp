#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	for (int i = 0; i < NBOIDS; i++) {
		flock.push_back(boid);
		flock[i].setup();
	}
	pdfRendering = false;
	oneShot = false;

	ofBeginSaveScreenAsPDF("screenshot-" + ofGetTimestampString() + ".pdf", false);
}

//--------------------------------------------------------------
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < NBOIDS - 1; i++) {
		flock[i].edges();
		flock[i].flocking(flock);
		flock[i].update();
		ofPoint start(flock[i].position);
		ofPoint end(flock[i].position + flock[i].velocity);
		ofPoint control1(flock[i+1].position);
		ofPoint	control2(flock[i+1].position + flock[i + 1].velocity);
		spline = ofxSandLine(start, control1, control2, end);
		spline.setColor(0);
		spline.setBreadth(2);
		spline.draw(1000);

	}

	if (oneShot) {
		ofEndSaveScreenAsPDF();
		oneShot = false;
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (!pdfRendering && key == 's') {
		oneShot = true;
	}
}