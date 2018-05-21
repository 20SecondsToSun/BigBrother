#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include <json/json.h>
#include "JsonParser.h"


namespace bbrother {
	class JsonParserFace: public JsonParser<Face> {
	public:
		JsonParserFace() {};
		JsonParserFace( string& json_str_ );
		virtual Face* Parse() override;
		//TODO: inheritance or templates
		//virtual string ParseFaceSetToken() override;
		virtual bool Valid() override;
		virtual void SetJsonStr(string& json_str_) override;

	private:
		virtual void setAttributes( Face* human, Json::Value faces );
		virtual void setFaceRectangle( Face* human, Json::Value faces );
		virtual void setFaceToken( Face* human, Json::Value faces );

		Json::Reader reader;
		Json::Value root;
		bool valid;
		string json_str;
	};
}