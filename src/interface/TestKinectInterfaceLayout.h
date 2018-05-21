#pragma once
#include "ofMain.h"
#include "TestInterfaceLayout.h"

namespace bbrother
{
	typedef ofPtr<class TestKinectInterfaceLayout> TestKinectInterfaceLayoutPtr;

	class TestKinectInterfaceLayout : public TestInterfaceLayout
	{
	public:
		TestKinectInterfaceLayout();

		virtual void update() override;
		virtual void draw() override;
		virtual ~TestKinectInterfaceLayout();

	private:
		ofPtr<ofxDatGuiButton> kinectStartButton, kinectStopButton, kinectShowFrames;
		ofPtr<ofxDatGuiLabel> peopleTrackedText;

		void kinectStartButtonClicked(ofxDatGuiButtonEvent event);
		void kinectStopButtonClicked(ofxDatGuiButtonEvent event);
		void kinectShowFramesButtonClicked(ofxDatGuiButtonEvent event);
	};
}

