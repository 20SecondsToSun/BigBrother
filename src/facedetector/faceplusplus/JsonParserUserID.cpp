#include "JsonParserUserID.h"

using namespace bbrother;

JsonParserUserID::JsonParserUserID( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

void JsonParserUserID::SetJsonStr( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

bool JsonParserUserID::Valid() {
	return valid;
}

int* JsonParserUserID::Parse() {
	if( valid ) {
		try {
			Json::Value candidates = root["results"];
			if( candidates.size() != 0 ) {
				//TODO: check most compatible
				double confidence = candidates[0]["confidence"].asDouble();
				if( confidence > 80 ) {
					int* user_id = new int();
					*user_id = std::stoi( candidates[0]["user_id"].asString() );
					return user_id;
				}
				return nullptr;
			} else {
				candidates = root["id"];
				int* user_id = new int();
				*user_id = candidates.asInt();
				return user_id;
			}
		} catch( exception e ) {
			std::cout << "Error while parsing UserID...";
			std::cout << e.what();
			return nullptr;
		}
	}
	return nullptr;
}