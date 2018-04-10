#include "JsonParserFace.h"

using namespace bbrother;

JsonParserFace::JsonParserFace( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

void JsonParserFace::SetJsonStr( string& json_str_ ) {
	json_str = json_str_;
	valid = reader.parse( json_str, root );
}

bool JsonParserFace::Valid() {
	return valid;
}

void JsonParserFace::setAttributes( Face* human, Json::Value faces ) {
	FaceAttributes tmp_attributes;
	tmp_attributes.age = faces[0]["attributes"]["age"].get( "value", 0 ).asInt();
	tmp_attributes.gender = faces[0]["attributes"]["gender"].get( "value", "non" ).asString();
	tmp_attributes.ethnicity = faces[0]["attributes"]["ethnicity"].get( "value", "non" ).asString();
	float female = faces[0]["attributes"]["beauty"].get( "female_score", 0 ).asFloat();
	float male = faces[0]["attributes"]["beauty"].get( "male_score", 0 ).asFloat();
	tmp_attributes.setBeauty( male, female );
	human->setAttributes( tmp_attributes );
}

void JsonParserFace::setFaceRectangle( Face* human, Json::Value faces ) {
	FaceRectangle rectangle;
	rectangle.height = faces[0]["face_rectangle"].get( "height", 0 ).asFloat();
	rectangle.left = faces[0]["face_rectangle"].get( "left", 0 ).asFloat();
	rectangle.top = faces[0]["face_rectangle"].get( "top", 0 ).asFloat();
	rectangle.width = faces[0]["face_rectangle"].get( "width", 0 ).asFloat();
	human->setFaceRectangle( rectangle );
}

void JsonParserFace::setFaceToken( Face* human, Json::Value faces ) {
	human->setToken( faces[0].get( "face_token", "0" ).asString() );
}

Face* JsonParserFace::Parse() {
	if( valid ) {
		try {
			Json::Value faces = root["faces"];
			assert( faces.size() == 1 ); // TODO error
			Face* human = new Face();

			setAttributes( human, faces );
			setFaceRectangle( human, faces );
			setFaceToken( human, faces );

			return human;
		} catch( exception e ) {
			std::cout << "Error parsing...";
			std::cout << e.what();
			return NULL;
		}
	}
	return NULL;
}

/*string JsonParserFace::ParseFaceSetToken() {
	if( valid ) {
		try {
			Json::Value token = root["faceset_token"];
			return token.asString();
		} catch( exception e ) {
			std::cout << "Error while parsing faceSetToken...";
			std::cout << e.what();
			return "\0";
		}
	}
	return "\0";
}*/