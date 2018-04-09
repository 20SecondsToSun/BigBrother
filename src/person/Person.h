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

	private:
		int id;
		KinectData kinectData;
		FaceData faceData;
	};
}

