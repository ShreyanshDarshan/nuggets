#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>
#define N 400

using namespace std;

Screen s(N, N);
//space_3d cam()
double prob(double x, double y)
{
	double r = sqrt(x*x + y*y);
	double f= 250.0*exp(-r/100) * cos(atan2(x, y)) * cos(atan2(x, y));
	int val = f;
	//cout<<val<<"\t";
	return f;
}


int main()
{
	for (double i=-N/2; i<N/2; i++)
	{
		for(double j=-N/2; j<N/2; j++)
		{
			//prob(i, j);
			s.put_pixel(N/2 + i, N/2 + j, 0, (int)prob(i, j), 0);
	//		if (prob(i, j)<0.0001 && prob(i, j)>-0.0001)
	//		s.put_pixel(N/2 + i, N/2 + j, 0, 0, 100);
		}
	}
	s.Draw();
	//getch();
	return 0;
}
