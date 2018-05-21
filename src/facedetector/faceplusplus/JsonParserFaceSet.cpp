#include "JsonParseFaceSet.h"

using namespace bbrother;

JsonParserFaceSet::JsonParserFaceSet( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

void JsonParserFaceSet::SetJsonStr( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

bool JsonParserFaceSet::Valid() {
	return valid;
}

string* JsonParserFaceSet::Parse() {
	if( valid ) {
		try {
			string* res = new string();
			Json::Value token = root["faceset_token"];
			*res = token.asString();
			return res;
		} catch( exception e ) {
			std::cout << "Error while parsing faceSetToken...";
			std::cout << e.what();
			return nullptr;
		}
	}
	return nullptr;
}