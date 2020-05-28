#include<iostream>
#include<conio.h>
#include<render.h>

using namespace std;

int main()
{
	Screen s(700, 300);
	space_3d cam(200, 0.1, 3.14/4, 3.14/4, 200, 200);
	for (float i=0; i<1000; i++)
	{
		s.line_3d(cam, -100, 0, 0, 100, 0, 0, 244, 0, 0);
		s.line_3d(cam, 0, -100, 0, 0, 100, 0, 0, 244, 0);
		s.line_3d(cam, 0, 0, -100, 0, 0, 100, 0, 0, 244);
		s.circle_3d(cam, 50, 50, 50, 10, 0, 100, 0, 100);
		//cam.track();
		//s.draw_path(0, 0, 100, 100, 100, 100, 100);
		s.Draw();
		Sleep(100);
		s.clear();
		cam.th+=0.1;
		//cam = space_3d(200, 0.3, 3.14/4 + i/30, 3.14/4 - i/20, 200, 200);
	}
	return 0;
}
