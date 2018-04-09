#pragma once
#include "ofMain.h"
#include "BaseScreen.h"

namespace bbrother
{
	typedef ofPtr<class DetectScreen> DetectScreenPtr;

	class DetectScreen : public BaseScreen
	{
	public:
		DetectScreen();
		virtual void show() override; //показываем через альфу текст("Bored.." пока)
		virtual void hide() override; //убираем через альфу текст.
		virtual void update() override;
		virtual void draw() override;

		virtual ~DetectScreen();
	private:
		ofImage image;
		ofTrueTypeFont font;
	};
}