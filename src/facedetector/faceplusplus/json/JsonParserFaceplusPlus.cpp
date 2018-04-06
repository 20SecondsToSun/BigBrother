#include "JsonParserFaceplusPlus.h"

using namespace bbrother;

JsonParserFaceplusPlus::JsonParserFaceplusPlus(const string& json):
	isParseSuccess(false)
{
	cout << json << endl;
	isValid = reader.parse(json, root);
	currentFace = FacePtr(new Face());
}

bool JsonParserFaceplusPlus::valid()
{
	return isValid;
}

void JsonParserFaceplusPlus::setAttributes(FacePtr face, Json::Value faces)
{
	FaceAttributes tmpAttributes;
	tmpAttributes.age = faces[0]["attributes"]["age"].get("value", 0).asInt();
	tmpAttributes.gender = faces[0]["attributes"]["gender"].get("value", "non").asString();
	tmpAttributes.ethnicity = faces[0]["attributes"]["ethnicity"].get("value", "non").asString();

	float female = faces[0]["attributes"]["beauty"].get("female_score", 0).asFloat();
	float male = faces[0]["attributes"]["beauty"].get("male_score", 0).asFloat();
	tmpAttributes.setBeauty(male, female);

	face->setAttributes(tmpAttributes);
}

void JsonParserFaceplusPlus::setFaceRectangle(FacePtr face, Json::Value faces)
{
	FaceRectangle rectangle;
	rectangle.height = faces[0]["face_rectangle"].get("height", 0).asFloat();
	rectangle.left = faces[0]["face_rectangle"].get("left", 0).asFloat();
	rectangle.top = faces[0]["face_rectangle"].get("top", 0).asFloat();
	rectangle.width = faces[0]["face_rectangle"].get("width", 0).asFloat();
	face->setFaceRectangle(rectangle);
}

void JsonParserFaceplusPlus::setFaceToken(FacePtr human, Json::Value faces)
{
	human->setToken(faces[0].get("face_token", "0").asString());
}

bool JsonParserFaceplusPlus::parse()
{
	if(isValid)
	{ 
		try
		{
			Json::Value faces = root["faces"];
			assert(faces.size() == 1); // TODO error		

			setAttributes(currentFace, faces);
			setFaceRectangle(currentFace, faces);
			setFaceToken(currentFace, faces);
			isParseSuccess = true;

		}
		catch(exception e) 
		{
			std::cout << "Error parsing...";
			std::cout << e.what();		
		}
	}

	return isParseSuccess;
}

FacePtr JsonParserFaceplusPlus::getFace() const
{
	return currentFace;
}