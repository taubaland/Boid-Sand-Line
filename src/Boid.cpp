#include "Boid.h"

Boid::Boid() {

};

void Boid::setup() {
    position = ofVec2f(ofRandomWidth(), ofRandomHeight());
    velocity = ofVec2f(ofRandom(2, 4), ofRandom(2, 4));
    acceleration = ofVec2f();
    maxForce = 0.1;
    maxSpeed = 2;
    dim = 5;
    
//    ofPolyline polyline;
    ofSetBackgroundColor(255);
    ofSetBackgroundAuto(false);
    ofSetColor(0);
 }

void Boid::edges() {
    if (this->position.x < 0) {
        //this->position.x = ofGetWidth();
        this->acceleration.x -= -1;
    }
    else if (this->position.x > ofGetWidth()) {
        //this->position.x = 0;
        this->acceleration.x += -1;
    }
    if (this->position.y < 0) {
        //this->position.y = ofGetHeight();
        this->acceleration.y -= -1;
    }
    else if (this->position.y > ofGetHeight()) {
        //this->position.y = 0;
        this->acceleration.y += -1;
    }
}

ofVec2f Boid::align(Boid boid, vector<Boid> flock) {
    float perceptionRadius = 10;
    ofVec2f steering;
    float total = 0;
    for (Boid other : flock) {
         float distance = ofDist(this->position.x, this->position.y, other.position.x, other.position.y);
        if (!(other.position == this->position) && distance < perceptionRadius) {
            steering += other.velocity;
            total++;
        }
    }
    if (total > 0) {
        steering /= total;
        steering.scale(maxSpeed);
        steering -= this->velocity;
        steering.limit(maxForce);
    }
    return steering;
}

ofVec2f Boid::separation(Boid boid, vector<Boid> flock) {
    float perceptionRadius = 250;
    ofVec2f steering;
    float total = 0;
    for (Boid other : flock) {
        float distance = ofDist(boid.position.x, boid.position.y, other.position.x, other.position.y);
        if (!(other.position == boid.position) && distance < perceptionRadius) {
            ofVec2f difference = boid.position - other.position;
            difference /= (distance * distance);
            steering += difference;
            total++;
        }
    }
    if (total > 0) {
        steering /= total;
        steering.scale(maxSpeed);
        steering -= boid.velocity;
        steering.limit(maxForce);
    }
    return steering;
}

ofVec2f Boid::cohesion(Boid boid, vector<Boid> flock) {
    float perceptionRadius = 200;
    ofVec2f steering;
    float total = 0;
    for (Boid other : flock) {
        float distance = ofDist(this->position.x, this->position.y, other.position.x, other.position.y);
        if (!(other.position == this->position) && distance < perceptionRadius) {
            ofVec2f difference = this->position - other.position;
            steering += other.position;
            total++;
        }
    }
    if (total > 0) {
        steering /= total;
        steering -= this->position;
        steering.scale(maxSpeed);
        steering -= this->velocity;
        steering.limit(maxForce);
    }
    return steering;
}

void Boid::flocking(vector<Boid> flock) {
    ofVec2f ali = this->align(*this, flock);
    ofVec2f coh = this->cohesion(*this, flock);
    ofVec2f sep = this->separation(*this, flock);
    this->acceleration += ali;
    this->acceleration += coh;
    this->acceleration += sep;
}

void Boid::update() {
    this->position += this->velocity;
    this->velocity += this->acceleration;
    this->velocity.limit(maxSpeed);
    this->acceleration *= 0;
}

void Boid::draw() {
}