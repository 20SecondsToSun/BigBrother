#include "Cloud.h"

using namespace bbrother;

Cloud::Cloud() 
{
	N = 256;
	spectrum = new float[N];
	bandRad = 2;
	bandVel = 100;

	for (int i = 0; i < N; i++) {
		spectrum[i] = 0.0f;
	}

	Rad = 500;
	Vel = 0.1;
	n = 300;
			
	tx = new float[n];
	ty = new float[n];
	p = new ofPoint[n];

	col = new ofColor[n];

	for (int j = 0; j < n; j++) {
		tx[j] = ofRandom(0, 1000);
		ty[j] = ofRandom(0, 1000);
	}

	time0 = 0;
}

void Cloud::update() 
{
	ofSoundUpdate();

	float *val = ofSoundGetSpectrum(N);
	
	for (int i = 0; i<N; i++) {
		spectrum[i] *= 0.97;
		spectrum[i] = max(spectrum[i], val[i]);
	}

	float time = ofGetElapsedTimef();
	float dt = time - time0;
	dt = ofClamp(dt, 0.0, 0.1);
	time0 = time;

	Rad = ofMap(spectrum[bandRad], 1, 3, 400, 800, true);
	Vel = ofMap(spectrum[bandVel], 0, 0.1, 0.05, 0.5);

	for (int j = 0; j<n; j++) {
		tx[j] += Vel * dt;
		ty[j] += Vel * dt;
							
		p[j].x = ofSignedNoise(tx[j]) * Rad;
		p[j].y = ofSignedNoise(ty[j]) * Rad;
	}
}

void Cloud::draw() 
{
	//ofBackground(255, 255, 255);
	ofBackground(0, 0, 0);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	ofSetColor(255, 0, 0);
	ofFill();
	for (int i = 0; i<n; i++) {
		ofCircle(p[i], 2);
	}

	float dist = 40;
	for (int j = 0; j<n; j++) {
		for (int k = j + 1; k<n; k++) {
			if (ofDist(p[j].x, p[j].y, p[k].x, p[k].y)
				< dist) {
				ofLine(p[j], p[k]);
			}
		}
	}

	ofPopMatrix();
}

Cloud::~Cloud() 
{
	delete[] p;
	delete[] ty;
	delete[] tx;
	delete[] spectrum;
}