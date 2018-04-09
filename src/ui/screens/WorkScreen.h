#pragma once
#include "ofMain.h"
#include "BaseScreen.h"
#include "../containers/BaseContainer.h"

namespace bbrother
{
	typedef ofPtr<class WorkScreen> WorkScreenPtr;

	class WorkScreen: public BaseScreen
	{
	public:
		WorkScreen();
		virtual void show() override;
		virtual void hide() override;
		virtual void update() override;
		virtual void draw() override;

		virtual void newPersonAppear(PersonPtr person);
		virtual void personRecognized(PersonPtr person);

		virtual bool isUsed();

		virtual ~WorkScreen();

		ofxCinderTimeline::Timeline& timeline() { return *mTimeline; }

	private:
		BaseContainerPtr detectCardsContainer;
		BaseContainerPtr recognizeCardsContainer;

		ofPtr<ofxCinderTimeline::Timeline> mTimeline;
		ofxCinderTimeline::Anim<float> visibility;

		ofTrueTypeFont font;
	};
}
