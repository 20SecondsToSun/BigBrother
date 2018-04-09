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
		int N; // ����� ����� �������
		float* spectrum;
		int bandRad;
		int bandVel;

		float Rad; // ������ ������
		float Vel; // �������� �������� ����� ������

		int n; // ����� ����� � ������
		
		float* tx;
		float* ty;
		ofPoint* p; // ���������� ����� ������

		ofColor* col;

		float time0; // ������������ ��� ���������� dt - ���������� ������� ����� �������������
	};
}