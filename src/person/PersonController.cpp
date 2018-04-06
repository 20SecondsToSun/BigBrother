#include "PersonController.h"

using namespace bbrother;

PersonController::PersonController()
{

}

PersonPtr PersonController::createNewPerson(const Tracker::TrackerPerson& trackerPerson)
{
	PersonPtr person;
	//person.rectangleImage = trackerPerson.image;
	//person.id = generateID();
	persons.push_back(person);
	ofNotifyEvent(newPersonCreated, person);
	return person;
}


PersonController::~PersonController()
{

}
