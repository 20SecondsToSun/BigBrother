#pragma once
#include "ofMain.h"
#include "Person.h"
#include "../tracker/Tracker.h"

namespace bbrother
{
	typedef ofPtr<class PersonController> PersonControllerPtr;

	class PersonController
	{
	public:
		PersonController();
		virtual ~PersonController();

		ofEvent<PersonPtr> newPersonCreated;

		PersonPtr createNewPerson(const Tracker::TrackerPerson& trackerPerson);

	private:
		vector<PersonPtr> persons;
	};
}

