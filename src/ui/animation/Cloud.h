#pragma once

#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Cloud> CloudPtr;

	class Cloud
	{
	public:
		Cloud();

		void update();
		void draw();

		virtual ~Cloud();
	private:
		int N; // Число полос спектра
		float* spectrum;
		int bandRad;
		int bandVel;

		float Rad; // радиус облака
		float Vel; // параметр скорости точек облака

		int n; // число точек в облаке
		
		float* tx;
		float* ty;
		ofPoint* p; // координаты точек облака

		ofColor* col;

		float time0; // используется для вычисления dt - прошедшего времени между отображениями
	};
}