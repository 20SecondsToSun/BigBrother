#include "JsonParserDB.h"

using namespace bbrother;
//COPY AND PASTE
JsonParserDB::JsonParserDB( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

void JsonParserDB::SetJsonStr( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

bool JsonParserDB::Valid() {
	return valid;
}
//end copy and paste

DataBaseParams* JsonParserDB::Parse() {
	if( valid ) {
		try {
			DataBaseParams* res = new DataBaseParams();
			res->expires_in = root["expires_in"].asString();
			res->access_token = root["access_token"].asString();
			res->refresh_token = root["refresh_token"].asString();

			return res;
		} catch( exception e ) {
			std::cout << "Error parsing...";
			std::cout << e.what();
			return NULL;
		}
	}
	return NULL;
}