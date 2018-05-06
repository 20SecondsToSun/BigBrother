#include "Person.h"

using namespace bbrother;

Person::Person()
{

}

Person::Person(int _id) {
	id = _id;
	if (_id % 2 == 1) {
		face.load("images/photo1.jpg");
	}
	else {
		face.load("images/photo2.jpg");
	}
}

Person::~Person()
{

}
