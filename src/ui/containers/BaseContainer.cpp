#include "BaseContainer.h"

using namespace bbrother;

BaseContainer::BaseContainer()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "BaseContainer");
}


void BaseContainer::update()
{
	//удаляем лишние карточки
	for (auto i = cards.begin(); i != cards.end();) {
		if (ofGetElapsedTimef() - i->get()->getCreationTime() > cardRotatorTime) {
			cards.erase(i);
			i = cards.begin();
		}
		else {
			i++;
		}
	}

	//обновляем позиции
	int num = 0;
	for (auto i = cards.begin(); i != cards.end(); i++) {
		i->get()->setLocationAnim(ofPoint(location.x + 120 * num + 10, location.y + 10));
		num++;
	}

	//обновляем карточки
	for (auto i = cards.begin(); i != cards.end(); i++) {
		i->get()->update();
	}
}

void BaseContainer::draw()
{
	for (auto i = cards.begin(); i != cards.end(); i++) {
		i->get()->draw();
	}
}

void BaseContainer::show()
{

}

void BaseContainer::hide()
{

}


bool BaseContainer::empty() {
	return cards.empty();
}


void BaseContainer::addCard(BaseCardPtr card)
{
	card->setSize(ofRectangle(0, 0 , 100, 150));
	card->setLocation(ofPoint(ofGetWidth() + 10, location.y + 10));
	cards.push_back(card);
}

void BaseContainer::removeCard(BaseCardPtr card)
{
	for (auto i = cards.begin(); i != cards.end();) {
		if (i->get()->getPerson()->getId() == card->getPerson()->getId()) {
			cards.erase(i);
			i = cards.begin();
		}
		else {
			i++;
		}
	}
}


void BaseContainer::setLocation(const ofPoint& _location)
{
	location = _location;
}


BaseContainer::~BaseContainer()
{

}
