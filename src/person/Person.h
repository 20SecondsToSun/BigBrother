#pragma once
#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Person> PersonPtr;

	struct FaceData
	{

	};

	struct KinectData
	{

	};

	class Person
	{
	public:
		Person();
		Person(int _id);
		virtual ~Person();
		int getId() {
			return id;
		}

		int id;
		ofImage face;
		KinectData kinectData;
		FaceData faceData;
	};
}

