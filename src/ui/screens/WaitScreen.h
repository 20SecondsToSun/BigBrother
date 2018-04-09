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

		virtual void show() override; //���������� ����� ����� �����("Bored.." ����)
		virtual void hide() override; //������� ����� ����� �����.
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

