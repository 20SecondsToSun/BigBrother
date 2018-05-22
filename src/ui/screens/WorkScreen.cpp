#include "WorkScreen.h"

using namespace bbrother;

WorkScreen::WorkScreen()
{
	mvisTimeline = ofxCinderTimeline::Timeline::create();
	mvisTimeline->stepTo(ofGetElapsedTimef());

	detectCardsContainer = BaseContainerPtr(new BaseContainer());
	detectCardsContainer->setLocation(ofPoint(100, 200));

	recognizeCardsContainer = BaseContainerPtr(new BaseContainer());
	recognizeCardsContainer->setLocation(ofPoint(100, ofGetHeight() - 300));

	font.load("ofxbraitsch/fonts/Starjout.ttf", 32);
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Work screen init");
}


void WorkScreen::show()
{
	//ofNotifyEvent(BaseScreen::showAnimationcomplete, this);
	vistimeline().stepTo(ofGetElapsedTimef());
	vistimeline().apply(&visibility, 255.0f, 1.0f, ofxCinderTimeline::EaseInOutSine()).finishFn(std::bind([this]() {ofNotifyEvent(BaseScreen::showAnimationcomplete, this); }));
}

void WorkScreen::hide()
{
	//ofNotifyEvent(BaseScreen::hideAnimationcomplete, this);
	vistimeline().stepTo(ofGetElapsedTimef());
	vistimeline().apply(&visibility, 0.0f, 1.0f, ofxCinderTimeline::EaseInOutSine()).finishFn(std::bind([this]() {ofNotifyEvent(BaseScreen::hideAnimationcomplete, this); }));
}

void WorkScreen::update()
{
	detectCardsContainer->setLocation(ofPoint(100, 150));
	recognizeCardsContainer->setLocation(ofPoint(100, ofGetHeight() - 350));

	detectCardsContainer->update();
	recognizeCardsContainer->update();

	vistimeline().stepTo(ofGetElapsedTimef());
}

void WorkScreen::draw()
{
	detectCardsContainer->draw();
	ofEnableAlphaBlending();

	ofSetColor(255, 255, 255, visibility.value());
	std::string msg = "Nice to see you..";
	ofRectangle bounds = font.getStringBoundingBox(msg, ofGetWidth() / 2, 100);

	ofSetColor(ofColor::white);
	font.drawString(msg, bounds.x - bounds.width / 2, bounds.y - bounds.height / 2);

	ofDisableAlphaBlending();

	recognizeCardsContainer->draw();
}


void WorkScreen::newPersonAppear(PersonPtr person)
{
	BaseCardPtr newCard (new BaseCard(person));
	detectCardsContainer->addCard(newCard);
}

void WorkScreen::personRecognized(PersonPtr person)
{
	BaseCardPtr newCard(new BaseCard(person));
	detectCardsContainer->removeCard(newCard);
	recognizeCardsContainer->addCard(newCard);
}


bool WorkScreen::isUsed() {
	return !detectCardsContainer->empty() || !recognizeCardsContainer->empty();
}


WorkScreen::~WorkScreen()
{

}
