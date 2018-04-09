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
		virtual void show() override; //���������� ����� ����� �����("Bored.." ����)
		virtual void hide() override; //������� ����� ����� �����.
		virtual void update() override;
		virtual void draw() override;

		virtual ~DetectScreen();
	private:
		ofImage image;
		ofTrueTypeFont font;
	};
}