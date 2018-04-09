#include "ScreenController.h"
#include "../person/Person.h"
#include "screens/WaitScreen.h"
#include "screens/WorkScreen.h"
#include "screens/DetectScreen.h"
#include "screens/ResultScreen.h"


using namespace bbrother;

ScreenController::ScreenController() 
{
	screens.push_back(BaseScreenPtr(new WaitScreen()));
	screens.push_back(BaseScreenPtr(new WorkScreen()));
	//screens.push_back(BaseScreenPtr(new DetectScreen()));
	//screens.push_back(BaseScreenPtr(new ResultScreen()));
	currentScreen = screens[0];
	ofLog(ofLogLevel::OF_LOG_NOTICE, "ScreenController init");
};


void ScreenController::update()
{
	currentScreen->update();

	ofSoundUpdate();

	//проверяем состояние экрана 
	if (dynamic_cast<WaitScreen*> (currentScreen.get()) == NULL) {
		if ((dynamic_cast<WorkScreen*> (currentScreen.get()) != NULL) && (! dynamic_cast<WorkScreen*>(currentScreen.get())->isUsed())) {
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
	if (dynamic_cast<WorkScreen*> (currentScreen.get()) == NULL) {
		toWorkScreen();
	}
	
	dynamic_cast<WorkScreen*>(screens[(int)ScreenState::Work].get())->newPersonAppear(person);
}

void ScreenController::personRecognized(PersonPtr person) 
{
	if (dynamic_cast<WorkScreen*> (currentScreen.get()) == NULL) {
		toWorkScreen();
	}

	reinterpret_cast<WorkScreen*>(screens[(int)ScreenState::Work].get())->personRecognized(person);
}

/*
void ScreenController::personNotRecognized(PersonPtr person) 
{
	
}
*/


void ScreenController::setScreen(ScreenState _state) {
	currentScreen = screens[(int)ScreenState::Work];
}

void ScreenController::setWaitScreen() {
	currentScreen = screens[(int)ScreenState::Wait];
	currentScreen->show();

	sound.loadSound("");
	sound.setLoop(true);
	sound.play();
}

void ScreenController::setWorkScreen() {
	currentScreen = screens[(int)ScreenState::Work];
	currentScreen->show();

	sound.loadSound("");
	sound.setLoop(true);
	sound.play();
}


void ScreenController::toWorkScreen() {
	currentScreen->hide();
	ofAddListener(currentScreen->hideAnimationcomplete, this, &ScreenController::setWorkScreen);
}

void ScreenController::toWaitScreen() {
	currentScreen->hide();
	ofAddListener(currentScreen->hideAnimationcomplete, this, &ScreenController::setWaitScreen);
}


ScreenController::~ScreenController() 
{

}