#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include <json/json.h>
#include "JsonParser.h"


namespace bbrother {
	class JsonParserFaceSet : public JsonParser<string> {
	public:
		JsonParserFaceSet() {};
		JsonParserFaceSet( string& json_str_ );
		virtual string* Parse() override;
		//TODO: inheritance or templates
		//virtual string ParseFaceSetToken() override;
		virtual bool Valid() override;
		virtual void SetJsonStr( string& json_str_ ) override;

	private:
		Json::Reader reader;
		Json::Value root;
		bool valid;
		string json_str;
	};
}