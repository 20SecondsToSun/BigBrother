#pragma once
#include "ofMain.h"
#include "ofxCinderTimeline.h"
#include "../cards/BaseCard.h"
#include <list>

namespace bbrother
{
	typedef ofPtr<class BaseContainer> BaseContainerPtr;

	class BaseContainer
	{
	public:
		BaseContainer();

		virtual void update();
		virtual void draw();
		virtual void show();
		virtual void hide();

		virtual void setLocation(const ofPoint&);

		virtual void addCard(BaseCardPtr card);
		virtual void removeCard(BaseCardPtr card);
		virtual bool empty();

		virtual ~BaseContainer();
	private:
		list<BaseCardPtr> cards;

		ofRectangle size;
		ofPoint location;

		ofRectangle cardSize = ofRectangle(0, 0, 200, 300);

		int ñardShowCount;

		float cardRotatorTime = 10.0f;
	};
}
