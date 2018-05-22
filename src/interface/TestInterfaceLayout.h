#pragma once
#include "../person/Person.h"
#include "ofMain.h"
#include "ofxDatGui.h"

namespace bbrother
{
	enum class InterfaceEventType
	{
		None,
		TrackingStart,
		TrackingStop,
		TryDetectHuman,

		NewPersonAppear,
		PersonRecognized,
	};

	struct MyEvent {
		MyEvent(InterfaceEventType _type, PersonPtr _person = nullptr) {
			type = _type;
			person = _person;
		}

		InterfaceEventType type;
		PersonPtr person;
	};

	typedef ofPtr<class TestInterfaceLayout> TestInterfaceLayoutPtr;

	class TestInterfaceLayout
	{
	public:
		TestInterfaceLayout();

		ofEvent<MyEvent> InterfaceEvent;

		virtual void update();
		virtual void draw();
		virtual ~TestInterfaceLayout();
		virtual void setVisibility(bool isVisible);
		virtual void setPosition(const ofPoint& position);

	protected:
		bool isVisible;
		ofPoint position;
		vector<ofPtr<ofxDatGuiComponent>> components;
	};
}

