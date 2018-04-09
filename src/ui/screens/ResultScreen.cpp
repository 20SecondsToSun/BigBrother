#include "ResultScreen.h"

using namespace bbrother;

ResultScreen::ResultScreen()
{
	font.load("ofxbraitsch/fonts/Verdana.ttf", 64);
	ofLog(ofLogLevel::OF_LOG_NOTICE, " Result Screen init");
}

void ResultScreen::show()
{

}

void ResultScreen::hide() {

}

void  ResultScreen::update()
{

}

void  ResultScreen::draw()
{
	ofBackground(255, 255, 255);
	ofSetColor(0, 0, 0);
	std::string msg = "ResultScreen";
	font.drawString(msg, ofGetWidth() / 2 - msg.size() * 36 / 2, ofGetHeight() / 2);
}

ResultScreen::~ResultScreen()
{

}