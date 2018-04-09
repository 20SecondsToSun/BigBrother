#pragma once
#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Config> ConfigPtr;

	class Config
	{
	public:
		enum apiField
		{
			FACEPROTOCOL,
			FACEHOST,
			FACEMETHOD,
			APIKEY,
			APISECRET
		};

		struct ApiConfig
		{
			std::string faceProtocol;
			std::string faceHost;
			std::string faceMethod;
			std::string apiKey;
			std::string apiSecret;
		};

		Config();

		ofEvent<void> loadCompleteEvent;
		ofEvent<void> loadErrorEvent;
		
		virtual void load();

		virtual const std::string& getApiField(apiField fieldName);

		virtual void setApiField(apiField fieldName, const std::string& value);

		virtual ~Config();

	private:
		static const std::string filePath;
		ApiConfig apiData;
	};
}

