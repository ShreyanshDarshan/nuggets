#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>
#define N 100
#define size 200
#define frm 10
#define inith 0.2
using namespace std;

Screen s(size, size);
space_3d cam(200, 0.00001, inith, 0.2, 100, 100);

double prob(double x, double y, double z, int l)
{
	double r = sqrt(x*x + y*y + z*z);
	double f;
	switch (l)
	{
		case 0: f= 15*exp(-r/10) * x*x/r/r; break;
		case 1: f= 15*exp(-r/10) * y*y/r/r; break;
		case 2: f= 15*exp(-r/10) * z*z/r/r; break;
	}
	int val = f;
	return f;
}

double prob2(double x, double y, double z)
{
	double r = sqrt(x*x + y*y + z*z);
	double f= 15*exp(-r/10) * z*z/r/r;
	int val = f;
	return f;
}

double prob3(double x, double y, double z)
{
	double r = sqrt(x*x + y*y + z*z);
	double f= 15*exp(-r/10) * y*y/r/r;
	int val = f;
	return f;
}

double pr[3][frm][size][size];
int main()
{
	for (int i=0; i<frm; i++)
	{
		for (int j=0; j<size; j++)
		{
			for (int k=0; k<size; k++)
			{
				pr[0][i][j][k]=0;
				pr[1][i][j][k]=0;
				pr[2][i][j][k]=0;
			}
		}
	}
	
	cam.th=inith;
	for (int l=0; l<3; l++)
	{
		for (int count=0; count<frm; count++)
		{	
			for (double i=-N/2; i<N/2; i++)
			{
				for (double j=-N/2; j<N/2; j++)
				{
					for (double k=-N/2; k<N/2; k++)
					{	
						//prob(i, j);
						int x, y;
						cam.make_3d(x, y, i, j, k);
						pr[l][count][x][y] += prob(i, j, k, l);
						
				//		cout<<y<<"\t";
				//		getch();
				//		if (prob(i, j)<0.0001 && prob(i, j)>-0.0001)
				//		s.put_pixel(N/2 + i, N/2 + j, 0, 0, 100);
					}
				}
			}
			cam.th += 6.28/frm;
			//s.put_pixel(10*count, 10*count, 0, 100, 0);
			//cam.track();
			//s.draw_path(0, 1, 100, 1, 100, 100, 100);
			cout<<count+(l*20);	
		}
	}
	
	
	for (int count=0; count<10000; count++)
	{
		for (int i=0; i<size; i++)
		{
			for (int j=0; j<size; j++)
			{
				if ((int)pr[0][count][i][j]>255)
				{
					pr[0][count][i][j]=255;
				}
				s.put_pixel(i, j, 0, (int)pr[0][count][i][j], 0);
			}
		}
		
		for (int i=0; i<size; i++)
		{
			for (int j=0; j<size; j++)
			{
				if ((int)pr[1][count][i][j]>255)
				{
					pr[1][count][i][j]=255;
				}
				s.put_pixel_2(i, j, (int)pr[1][count][i][j], 0, 0);
			}
		}
		
		for (int i=0; i<size; i++)
		{
			for (int j=0; j<size; j++)
			{
				if ((int)pr[2][count][i][j]>255)
				{
					pr[2][count][i][j]=255;
				}
				s.put_pixel_2(i, j, 0, 0, (int)pr[2][count][i][j]);
			}
		}
		//cout<<1;
		s.Draw();
		s.clear();
		Sleep(100);
		//cam.track();
	}
	//getch();
	return 0;
}
