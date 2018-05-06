#pragma once
#include "ofMain.h"
#include "ofxCinderTimeline.h"

namespace bbrother
{
	typedef ofPtr<class BaseScreen> BaseScreenPtr;

	class BaseScreen
	{
	public:
		BaseScreen();

		ofEvent<void> showAnimationcomplete;
		ofEvent<void> hideAnimationcomplete;

		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;

		virtual ~BaseScreen();
	};
}

