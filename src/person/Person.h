#pragma once
#include "ofMain.h"
#include <string>

namespace bbrother
{
	typedef ofPtr<class Person> PersonPtr;

	struct FaceData
	{
		bool is;
		std::string name;
	};

	struct KinectData
	{
		bool is;
		ofImage body;
	};

	class Person
	{
	public:
		Person();
		Person(int _id, ofImage& pic);
		virtual ~Person();

		int id;
		KinectData kinectData;
		FaceData faceData;
	};
}

