#pragma once
#include "ofMain.h"
#include "BaseScreen.h"

namespace bbrother
{
	typedef ofPtr<class WaitScreen> WaitScreenPtr;

	class WaitScreen : public BaseScreen
	{
	public:
		WaitScreen();

		virtual void show() override; //показываем через альфу текст("Bored.." пока)
		virtual void hide() override; //убираем через альфу текст.
		virtual void update() override;
		virtual void draw() override;

		virtual ~WaitScreen();

		ofxCinderTimeline::Timeline& timeline() { return *mTimeline; }
		ofxCinderTimeline::Timeline& movetimeline() { return *mmoveTimeline; }

	private:
		ofPtr<ofxCinderTimeline::Timeline> mTimeline;
		ofPtr<ofxCinderTimeline::Timeline> mmoveTimeline;
		ofxCinderTimeline::Anim<float> visibility = 255;
		ofxCinderTimeline::Anim<ofPoint> location;

		ofTrueTypeFont font;
	};
}

