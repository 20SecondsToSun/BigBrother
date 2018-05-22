#include "ScreenController.h"
#include "../person/Person.h"
#include "screens/WaitScreen.h"
#include "screens/WorkScreen.h"
#include "screens/DetectScreen.h"
#include "screens/ResultScreen.h"

using namespace bbrother;

ScreenController::ScreenController() 
{
	screens.insert(std::pair< ScreenState, WaitScreenPtr> (ScreenState::Wait, WaitScreenPtr(new WaitScreen())));
	screens.insert(std::pair< ScreenState, WorkScreenPtr>(ScreenState::Work, WorkScreenPtr(new WorkScreen())));
	currentScreen = screens.find(ScreenState::Wait)->second;
	ofLog(ofLogLevel::OF_LOG_NOTICE, "ScreenController init");
};


void ScreenController::update()
{
	currentScreen->update();

	if (currentState != ScreenState::Wait) {
		if ((currentState == ScreenState::Work) && (!dynamic_cast<WorkScreen*>(currentScreen.get())->isUsed())) {
			toWaitScreen();
		}
	}
}

void ScreenController::draw() 
{
	currentScreen->draw();
}


void ScreenController::newPersonAppear(PersonPtr person) 
{
	if (currentState != ScreenState::Work) {
		toWorkScreen();
	}
	
	reinterpret_cast<WorkScreen*>(screens.find(ScreenState::Work)->second.get())->newPersonAppear(person);
}

void ScreenController::personRecognized(PersonPtr person) 
{
	if (currentState != ScreenState::Work) {
		toWorkScreen();
	}

	reinterpret_cast<WorkScreen*>(screens.find(ScreenState::Work)->second.get())->personRecognized(person);
}

void ScreenController::setCurrentState(ScreenState state) {
	currentState = state;
	currentScreen = screens.find(currentState)->second;
}


void ScreenController::toWorkScreen() {
	//currentScreen->hide();
	//ofAddListener(currentScreen->hideAnimationcomplete, this, &ScreenController::setWorkScreen);
	ScreenController::setWorkScreen();
}

void ScreenController::toWaitScreen() {
	//currentScreen->hide();
	//ofAddListener(currentScreen->hideAnimationcomplete, this, &ScreenController::setWaitScreen);
	ScreenController::setWaitScreen();
}


void ScreenController::setWaitScreen() {
	setCurrentState(ScreenState::Wait);
	currentScreen->show();
}

void ScreenController::setWorkScreen() {
	setCurrentState(ScreenState::Work);
	currentScreen->show();
}

void ScreenController::changeScreen() {
	if (currentState == ScreenState::Wait) {
		setCurrentState(ScreenState::Work);
	}
	else {
		setCurrentState(ScreenState::Wait);
	}
	currentScreen->show();
}


ScreenController::~ScreenController() 
{

}