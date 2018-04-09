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
		virtual void show(); //запускается стартовую анимацию появления всех компонентов экрана
		virtual void hide(); //запускается финальную анимацию всех компонентов экрана

		virtual void setLocation(const ofPoint&);

		virtual void addCard(BaseCardPtr card); //добавляем карточку
		virtual void removeCard(BaseCardPtr card);	//удаляем карточку
		virtual bool empty();

		virtual ~BaseContainer();
	private:
		list<BaseCardPtr> cards; //массив карточек

		//ofRectangle size; //размер карточек
		ofPoint location; //координаты контейнера

		//int сardShowCount; //количество карточек для одновременного показа

		float cardRotatorTime = 10.0f; //время жизни картчки
	};
}
