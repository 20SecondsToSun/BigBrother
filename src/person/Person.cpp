#include "Person.h"

using namespace bbrother;

Person::Person()
{

}

Person::Person(int _id, ofImage& pic) {
	id = _id;
	kinectData.body = pic;
	kinectData.is = true;
	faceData.is = false;
}

Person::~Person()
{

}
