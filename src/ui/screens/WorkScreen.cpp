#include "WorkScreen.h"

using namespace bbrother;

WorkScreen::WorkScreen()
{
	mTimeline = ofxCinderTimeline::Timeline::create();
	mTimeline->stepTo(ofGetElapsedTimef());

	detectCardsContainer = BaseContainerPtr(new BaseContainer());
	detectCardsContainer->setLocation(ofPoint(0, 0)); 
	recognizeCardsContainer = BaseContainerPtr(new BaseContainer());
	recognizeCardsContainer->setLocation(ofPoint(0, ofGetHeight() - 170));

	font.load("ofxbraitsch/fonts/Verdana.ttf", 64);
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Work screen init");
}


void WorkScreen::show()
{
	ofNotifyEvent(BaseScreen::showAnimationcomplete, this);
	//timeline().apply(&visibility, 255.0f, 1.0f, ofxCinderTimeline::EaseInOutSine()).finishFn(std::bind([this]() {ofNotifyEvent(BaseScreen::showAnimationcomplete, this); }));
}

void WorkScreen::hide()
{
	ofNotifyEvent(BaseScreen::hideAnimationcomplete, this);
	//timeline().apply(&visibility, 0.0f, 1.0f, ofxCinderTimeline::EaseInOutSine()).finishFn(std::bind([this]() {ofNotifyEvent(BaseScreen::hideAnimationcomplete, this); }));
}

void WorkScreen::update()
{
	detectCardsContainer->update();
	recognizeCardsContainer->update();

	timeline().stepTo(ofGetElapsedTimef());
}

void WorkScreen::draw()
{
	detectCardsContainer->draw();
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
