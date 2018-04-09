#include "WaitScreen.h"

using namespace bbrother;

WaitScreen::WaitScreen()
{
	mTimeline = ofxCinderTimeline::Timeline::create();
	mTimeline->stepTo(ofGetElapsedTimef());
	font.load("ofxbraitsch/fonts/Starjout.ttf", 64);
	location = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	movetimeline().appendTo(&location, location.value() - ofPoint(30, 0), location.value() + ofPoint(30, 0), 2.0f, ofxCinderTimeline::EaseInOutSine()).pingPong().loop();
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Wait Screen init");
}


void WaitScreen::show()
{
	timeline().apply(&visibility, 0.0f, 255.0f, 2.0f, ofxCinderTimeline::EaseInOutCubic()).finishFn(std::bind([this](){ofNotifyEvent(BaseScreen::showAnimationcomplete, this); }));
}

void WaitScreen::hide()
{
	timeline().apply(&visibility, 255.0f, 0.0f, 1.0f, ofxCinderTimeline::EaseInOutCubic()).finishFn(std::bind([this]() {ofNotifyEvent(BaseScreen::hideAnimationcomplete, this); }));
}

void WaitScreen::update()
{
	timeline().stepTo(ofGetElapsedTimef());
}

void WaitScreen::draw()
{
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, visibility.value());
	std::string msg = "Bored..";
	font.drawString(msg, location.value().x - msg.size() * 32 / 2, location.value().y);
	ofDisableAlphaBlending();
}


WaitScreen::~WaitScreen()
{

}
