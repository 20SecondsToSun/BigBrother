#pragma once
#include "ofMain.h"
#include "TestInterfaceLayout.h"

namespace bbrother
{
	typedef ofPtr<class TestMainUIInterfaceLayout> TTestMainUIInterfaceLayoutPtr;

	class TestMainUIInterfaceLayout : public TestInterfaceLayout
	{
	public:
		TestMainUIInterfaceLayout();

		virtual void update() override;
		virtual void draw() override;
		virtual ~TestMainUIInterfaceLayout();

	private:
		ofPtr<ofxDatGuiButton> screen1btn, screen2btn, screen3btn;

		void screen1ButtonClicked(ofxDatGuiButtonEvent event);
		void screen2ButtonClicked(ofxDatGuiButtonEvent event);
		void screen3ButtonClicked(ofxDatGuiButtonEvent event);
	};
}

