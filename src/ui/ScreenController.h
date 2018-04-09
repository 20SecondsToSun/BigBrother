#pragma once
#include "ofMain.h"
#include "screens/BaseScreen.h"
#include "../person/Person.h"
#include <vector>



namespace bbrother
{
	typedef ofPtr<class ScreenController> ScreenControllerPtr;

	enum class ScreenState
	{
		Wait,
		Work,
		Errror
		//Detect,
		//Result
	};

	class ScreenController
	{
	public:
		ScreenController();

		ofEvent<void> loadCompleteEvent;
		ofEvent<void> loadErrorEvent;

		virtual void update();
		virtual void draw();

		void newPersonAppear(PersonPtr person);
		void personRecognized(PersonPtr person);
		//void personNotRecognized(PersonPtr person);

		void setScreen(ScreenState _state);
		void setWaitScreen();
		void setWorkScreen();

		void toWaitScreen();
		void toWorkScreen();

		virtual ~ScreenController();

	private:
		BaseScreenPtr currentScreen;
		vector<BaseScreenPtr> screens;

		ofSoundPlayer sound;
	};
}