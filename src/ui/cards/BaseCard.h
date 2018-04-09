#pragma once
#include "ofMain.h"
#include "ofxCinderTimeline.h"
#include "../../person/Person.h"

namespace bbrother
{
	typedef ofPtr<class BaseCard> BaseCardPtr;

	class BaseCard
	{
	public:
		BaseCard();
		BaseCard(PersonPtr _person);

		virtual void update();
		virtual void draw();
		virtual void show(); //запускается стартовую анимацию появления всех компонентов экрана
		virtual void hide(); //запускается финальную анимацию всех компонентов экрана

		void setLocationAnim(ofPoint _location);
		void setLocation(ofPoint _location);

		void setSize(ofRectangle _size);

		virtual ~BaseCard();

		//bool operator < (const BaseCard &other) const;
		float getCreationTime();
		PersonPtr getPerson();

		ofxCinderTimeline::Timeline& timeline() { return *mTimeline; }

	private:
		
		PersonPtr person; //указатель на пользователя
		ofRectangle size; //карточка
		ofRectangle imageSize; //изображение человека

		float creationTime;

		ofPtr<ofxCinderTimeline::Timeline> mTimeline;
		ofxCinderTimeline::Anim<ofPoint> location;
		ofPoint targetLocation;
	};
}
