#include "DetectScreen.h"

using namespace bbrother;

DetectScreen::DetectScreen()
{
	font.load("ofxbraitsch/fonts/Verdana.ttf", 64);
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Detect Screen init");
}

void DetectScreen::show()
{

}

void DetectScreen::hide()
{

}

void DetectScreen::update()
{

}

void DetectScreen::draw()
{
	ofBackground(255, 255, 255);
	ofSetColor(0, 0, 0);
	std::string msg = "DetectScreen";
	font.drawString(msg, ofGetWidth() / 2 - msg.size() * 36 / 2, ofGetHeight() / 2);
}

DetectScreen::~DetectScreen()
{

}