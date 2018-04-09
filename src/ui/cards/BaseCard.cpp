#include "BaseCard.h"

using namespace bbrother;

BaseCard::BaseCard()
{
	mTimeline = ofxCinderTimeline::Timeline::create();
	mTimeline->stepTo(ofGetElapsedTimef());

	creationTime = ofGetElapsedTimef();
	ofLog(ofLogLevel::OF_LOG_NOTICE, "BaseCard init");
}

BaseCard::BaseCard(PersonPtr _person) 
{
	mTimeline = ofxCinderTimeline::Timeline::create();
	mTimeline->stepTo(ofGetElapsedTimef());
	person = _person;
	creationTime = ofGetElapsedTimef();
	ofLog(ofLogLevel::OF_LOG_NOTICE, "BaseCard init");
}


void BaseCard::update()
{
	timeline().stepTo(ofGetElapsedTimef());
}

void BaseCard::draw()
{
	ofSetColor(230, 230, 230);
	ofFill();
	size.setPosition(location);
	ofDrawRectangle(size);
}

void BaseCard::show()
{
}

void BaseCard::hide()
{

}


void BaseCard::setLocationAnim(ofPoint _location)
{
	if (_location != targetLocation) {
		timeline().apply(&location, _location, 2.0f, ofxCinderTimeline::EaseInOutCubic());
		targetLocation = _location;
	}
}

void BaseCard::setLocation(ofPoint _location) {
	targetLocation = _location;
	location = _location;
}


void BaseCard::setSize(ofRectangle _size)
{
	size = _size;
}


BaseCard::~BaseCard()
{

}

/*
bool BaseCard::operator < (const BaseCard &other) const {
	return person->getId() < other.person->getId();
}
*/

float BaseCard::getCreationTime() {
	return creationTime;
}

PersonPtr BaseCard::getPerson() {
	return person;
}
