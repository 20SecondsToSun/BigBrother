#include "WaitScreen.h"

using namespace bbrother;

WaitScreen::WaitScreen()
{
	mvisTimeline = ofxCinderTimeline::Timeline::create();
	mvisTimeline->stepTo(ofGetElapsedTimef());

	mmoveTimeline = ofxCinderTimeline::Timeline::create();
	mmoveTimeline->stepTo(ofGetElapsedTimef());
	

	font.load("ofxbraitsch/fonts/Starjout.ttf", 32);

	movetimeline().appendTo(&disp,ofPoint(-30, 0), ofPoint(30, 0), 2.0f, ofxCinderTimeline::EaseInOutSine()).pingPong().loop();
	
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Wait Screen init");
}


void WaitScreen::show()
{
	vistimeline().stepTo(ofGetElapsedTimef());
	vistimeline().apply(&visibility, 255.0f, 1.0f, ofxCinderTimeline::EaseInOutCubic()).finishFn(std::bind([this](){ofNotifyEvent(BaseScreen::showAnimationcomplete, this); }));
}

void WaitScreen::hide()
{
	vistimeline().stepTo(ofGetElapsedTimef());
	vistimeline().apply(&visibility, 0.0f, 1.0f, ofxCinderTimeline::EaseInOutCubic()).finishFn(std::bind([this]() {ofNotifyEvent(BaseScreen::hideAnimationcomplete, this); }));
}

void WaitScreen::update()
{
	vistimeline().stepTo(ofGetElapsedTimef());
	movetimeline().stepTo(ofGetElapsedTimef());
}

void WaitScreen::draw()
{
	ofEnableAlphaBlending();

	ofSetColor(255, 255, 255, visibility.value());
	std::string msg = "Bored..";
	ofRectangle bounds = font.getStringBoundingBox(msg, ofGetWidth() / 2 + disp.value().x, ofGetHeight() / 2 + disp.value().y);

	ofSetColor(ofColor::white);
	font.drawString(msg, bounds.x - bounds.width / 2, bounds.y - bounds.height / 2);

	ofDisableAlphaBlending();
}


WaitScreen::~WaitScreen()
{

}
