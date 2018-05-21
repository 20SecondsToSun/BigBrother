#include "FacePlusPlusTypes.h"

using namespace bbrother;

FaceRectangle::FaceRectangle(float t, float l, float w, float h)
	:top(t), left(l), width(w), height(h)
{

}

FaceRectangle::FaceRectangle()
{

}

void FaceAttributes::setBeauty(float maleScore, float femaleScore)
{
	beauty.maleScore = maleScore;
	beauty.femaleScore = femaleScore;
}

Face::Face()
{

}

void Face::setToken(const string& token)
{
	this->token = token;
}

string Face::getToken() const
{
	return token;
}

void Face::setFaceRectangle(const FaceRectangle& faceRectangle)
{
	this->faceRectangle = faceRectangle;
}

FaceRectangle Face::getFaceRectangle() const
{
	return faceRectangle;
}

void Face::setLandmark(const vector<ofPoint>& landmark)
{
	this->landmark = landmark;
}

vector<ofPoint> Face::getLandmark() const
{
	return landmark;
}

void Face::setAttributes(const FaceAttributes& attributes)
{
	this->attributes = attributes;
}

void Face::Print() const {
	attributes.Print();
	faceRectangle.Print();
	std::cout << "token: " << token << std::endl;
}

void FaceRectangle::Print() const {
	std::cout << "height: " << height << std::endl;
	std::cout << "top: " << top << std::endl;
	std::cout << "left: " << left << std::endl;
	std::cout << "width: " << width << std::endl;
}

void FaceAttributes::Print() const {
	std::cout << "gender: " << gender << std::endl;
	std::cout << "age: " << age << std::endl;
	std::cout << "ethnity: " << ethnicity << std::endl;
	std::cout << "beauty female: " << beauty.femaleScore << std::endl;
	std::cout << "beauty male: " << beauty.maleScore << std::endl;
}

FaceAttributes Face::getAttributes() const
{
	return attributes;
}

Beauty Face::getBeauty() const
{
return attributes.beauty;
}
