#include "BaseCard.h"

using namespace bbrother;

BaseCard::BaseCard()
{
	mmoveTimeline = ofxCinderTimeline::Timeline::create();
	mmoveTimeline->stepTo(ofGetElapsedTimef());

	creationTime = ofGetElapsedTimef();

	font.load("ofxbraitsch/fonts/Starjout.ttf", 16);
	ofLog(ofLogLevel::OF_LOG_NOTICE, "BaseCard init");
}

BaseCard::BaseCard(PersonPtr _person) 
{
	mmoveTimeline = ofxCinderTimeline::Timeline::create();
	mmoveTimeline->stepTo(ofGetElapsedTimef());
	person = _person;
	creationTime = ofGetElapsedTimef();

	font.load("ofxbraitsch/fonts/Starjout.ttf", 16);
	ofLog(ofLogLevel::OF_LOG_NOTICE, "BaseCard init");
}


void BaseCard::update()
{
	movetimeline().stepTo(ofGetElapsedTimef());
}

void BaseCard::draw()
{
	person.get()->face.resize(size.getWidth() / 2, size.getHeight() / 2);
	person.get()->face.draw(location);

	ofSetColor(255, 255, 255);
	std::string msg = "Hi, Jackie!";
	font.drawString(msg, location.value().x, location.value().y + size.getHeight() / 2 + 20);
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
		movetimeline().stepTo(ofGetElapsedTimef());
		movetimeline().apply(&location, _location, 2.0f, ofxCinderTimeline::EaseInOutCubic());
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

float BaseCard::getCreationTime() {
	return creationTime;
}

PersonPtr BaseCard::getPerson() {
	return person;
}
