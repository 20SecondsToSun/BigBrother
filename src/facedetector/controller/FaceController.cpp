#include "FaceController.h"

using namespace bbrother;

FaceController::FaceController()
{
	familyBaseController = FamilyBaseControllerPtr(new FamilyBaseController());
	facePlusPlusDetector = FacePlusPlusDetectorPtr(new FacePlusPlusDetector());
	facePlusPlusSearcher = FacePlusPlusSearcherPtr(new FacePlusPlusSearcher());
}

void FaceController::init(ConfigPtr config)
{
	familyBaseController->init(config);
	facePlusPlusDetector->init(config);
}

void FaceController::update()
{
	facePlusPlusDetector->update();
	familyBaseController->update();
}

void FaceController::newPersonAppear(PersonPtr person)
{
	//facePlusPlusDetector->processImage("face.jpg");
	ofImage faceImage;
	faceImage.load("face.jpg");
	facePlusPlusDetector->processImage(faceImage);
}

void FaceController::onFaceDetect(PersonPtr person)
{
	//search in face set
	//....

	ofNotifyEvent(personFoundInFaceSet, person);
}

void FaceController::onFaceNotDetect()
{
	//face not detect on image
}

void FaceController::onFaceDetectorError()
{

}



void FaceController::onFaceFoundInFaceSet(PersonPtr person)
{
	//get user info from family base
	//....
}

void FaceController::onFaceNotFoundInFaceSet()
{

}

void FaceController::onFaceSearchError()
{

}



FaceController::~FaceController()
{

}