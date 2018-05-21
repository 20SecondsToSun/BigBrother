#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include <json/json.h>
#include "JsonParser.h"
#include "FaceDataBaseHandler.h"


namespace bbrother {
	class JsonParserDB: public JsonParser<DataBaseParams> {
	public:
		JsonParserDB() {};
		JsonParserDB( string& json_str_ );
		virtual DataBaseParams* Parse() override;
		virtual bool Valid() override;
		virtual void SetJsonStr( string& json_str_ ) override;

	private:
		Json::Reader reader;
		Json::Value root;
		bool valid;
		string json_str;
	};
}
