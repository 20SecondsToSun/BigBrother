#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"
#include <json/json.h>


namespace bbrother {
	template <class T>
	class JsonParser {
	public:
		JsonParser() {};
		JsonParser( string& json_str_ ) {};
		virtual T* Parse() = 0;
		virtual bool Valid() = 0;
		virtual void SetJsonStr( string& json_str_ ) = 0;

	private:
		Json::Reader reader;
		Json::Value root;
		bool valid;
		string json_str;
	};
}