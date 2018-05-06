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

		virtual void show() override;
		virtual void hide() override;
		virtual void update() override;
		virtual void draw() override;

		virtual ~WaitScreen();

		ofxCinderTimeline::Timeline& vistimeline() { return *mvisTimeline; }
		ofxCinderTimeline::Timeline& movetimeline() { return *mmoveTimeline; }

	private:
		ofPtr<ofxCinderTimeline::Timeline> mvisTimeline;
		ofPtr<ofxCinderTimeline::Timeline> mmoveTimeline;

		ofxCinderTimeline::Anim<float> visibility = 255;
		ofxCinderTimeline::Anim<ofPoint> disp;

		ofTrueTypeFont font;
	};
}

