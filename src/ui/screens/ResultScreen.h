#pragma once
#include "ofMain.h"
#include "BaseScreen.h"

namespace bbrother
{
	typedef ofPtr<class  ResultScreen>  ResultScreenPtr;

	class  ResultScreen : public BaseScreen
	{
	public:
		ResultScreen();
		virtual void show() override; //показываем через альфу текст("Bored.." пока)
		virtual void hide() override; //убираем через альфу текст.
		virtual void update() override;
		virtual void draw() override;

		virtual ~ResultScreen();

	private:
		ofImage image;
		ofTrueTypeFont font;
	};
}