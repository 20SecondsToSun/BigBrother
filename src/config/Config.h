#pragma once
#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Config> ConfigPtr;

	class Config
	{
	public:
		struct FacePlusPlusData
		{
			std::string faceProtocol;
			std::string faceHost;
			std::string faceDetectMethod;
			std::string faceSearchMethod;
			std::string APIKey;
			std::string APISecret;
		};

		struct FamilyBaseData
		{
			std::string familyProtocol;
			std::string familyHost;
			std::string grantType;
			int clientId;
			std::string clientSecret;
			std::string username;
			std::string password;
		};

		struct KinectData
		{
			int depthWidth;
			int depthHeight;
			int colorWidth;
			int colorHeight;
		};

		struct UIData
		{

		};

		Config();

		void setFacePlusPlusData(const FacePlusPlusData& facePlusPlusData);
		void setFamilyBaseData(const FamilyBaseData& familyBaseData);
		void setKinectData(const KinectData& kinectData);

		FacePlusPlusData getFacePlusPlusData() const;
		FamilyBaseData getFamilyBaseData() const;
		KinectData getKinectData() const;

		~Config();

	private:
		FacePlusPlusData facePlusPlusData;
		FamilyBaseData familyBaseData;
		KinectData kinectData;
		UIData uiData;
	};
}
