#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>
#define size 300
//#define zup 1000
#define mu 1.4
//#define d 100
#define fac 1
using namespace std;

float d = 100;
float zup = 1000;
Screen s(fac*size, fac*size);

struct vect
{
	float x, y, z;
};	


vect add(vect v1, vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

vect mult(float k, vect v)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
	return v;
}

float mod(vect v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float dist(vect r1, vect r2)
{
	return mod(add(r1, mult(-1, r2)));
}

float dot(vect v1, vect v2)
{
	return v1.x*v2.x + v1.z*v2.z + v1.y*v2.y;
}

POINT cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	m.y=fac*size-m.y;
//	POINT p;
//	p.x=rand()%size;
//	p.y=rand()%size;
	return m;
}
float time=0;
vect f(float x, float y, float tx, float ty)
{
	x-=tx;
	y-=ty;
//	vect n={x*exp((-x*x -y*y)/4000)/200, y*exp((-x*x -y*y)/4000)/200, 1};
	vect n={x/60, y/60, -1};
//	vect n={0.4*x*sin(sqrt(x*x+y*y)/4 + time/3)/sqrt(x*x+y*y), 0.4*y*sin(sqrt(x*x+y*y)/4 + time/3)/sqrt(x*x+y*y), 1};	
//	vect n={-x*sin(sqrt(x*x+y*y)/2 + time/3)/(x*x+y*y), -y*sin(sqrt(x*x+y*y)/2 + time/3)/(x*x+y*y), 1};	
//	vect n={0, 0, 1};
//	if ((1600 - x*x/4/3600 - y*y/4/3600)>0)
//	vect n={x/60, y/60, sqrt(1600 - x*x/4/3600 - y*y/4/3600)/60};	
	return mult(1/mod(n), n);
}

/*vect g(float x, float y, float tx, float ty)
{
	x-=tx;
	y-=ty;
//	vect n={x*exp((-x*x -y*y)/4000)/200, y*exp((-x*x -y*y)/4000)/200, 1};
//	vect n={x/300, y/300, 1};
	return mult(1/mod(n), n);
}
*/
void see(float &x_, float &y_, float x, float y, float tx, float ty)
{
	vect inc={size/2-x, size/2-y, zup};
	inc = mult(1/mod(inc), inc);
	vect dir = mult(dot(inc, f(x, y, tx, ty)), f(x, y, tx, ty)); //dir becomes component along normal
//	cout<<f(x, y).x;
	vect comp = dir;  // comp ""
	dir= add(inc, mult(-1, dir)); //dir becomes component perpendicular to normal
	float th=atan2(mod(dir), mod(comp));//acos(dot(inc, f(x, y, tx, ty)));
	float al=asin(sin(th)/mu);
	dir = mult(mod(comp)*tan(al)/mod(dir), dir); // dir becomes required component
	
	vect inc2 = add(dir, comp);  // inc2 becomes new incident ray

/*	inc2 = mult(1/mod(inc2), inc2);
//	cout<<inc2.x;
	float th2=acos(dot(inc2, g(x, y, t)));
	float al2=asin(sin(th2)/mu);
	vect dir2 = mult(dot(inc2, g(x, y, t)), g(x, y, t)); //dir becomes component along normal
	vect comp2 = dir2;  // comp ""
	dir2= add(inc2, mult(-1, dir2)); //dir becomes component perpendicular to normal
	dir2 = mult(mod(comp2)*tan(al2)/mod(dir2), dir2); // dir becomes required component
	
	inc2 = add(comp2, dir2);
*/
	float L = -d/inc2.z;
	x_=x+L*inc2.x;
	//cout<<inc2.x;
	y_=y+L*inc2.y;

}

float colR[size][size], colG[size][size], colB[size][size];

void display(int x, int y, float tx, float ty)
{
	float x_, y_;
	see(x_, y_, x, y, tx, ty);//cursor().x/fac, cursor().y/fac);
	if (x_>0 && x_<size && y_>0 && y_<size)
	{
	//	if (!((int(x_)%30)==0 || (int(y_)%30)==0))
		for (int k=0; k<fac; k++)
		for (int l=0; l<fac; l++)
		{
		//	colR[k][l]+=int(x_/5)%15;
		//	colB[k][l]+=int(x_/5)%15;
		//	colG[k][l]+=int(x_/5)%15;
		s.put_pixel(x*fac+k, y*fac+l, (int(x_)/5)*15 + 30,0, (int(y_)/5)*15 + 30);
		}
	}
}


int main()
{
//	cout<<2;
//	getch();
	int t;//-size;
	while (1)
	{
		time-=3;
		POINT P=cursor();
		P.x/=fac;
		P.y/=fac;
		for (int i=0; i<size; i++)
		{
			for (int j=0; j<size; j++)
			{
				display(i, j, P.x, P.y);
			//	s.put_pixel(i, j, 100, 0, 0);
			}
		}
/*		for (float i=-size/2; i<size/2; i++)
		{
			s.put_pixel(i+size/2, size+20+10*exp((-i*i)/4000), 100, 100, 100);
		}
*/		s.Draw();
		s.clear();
		d+=100;
//		zup-=10;
//		cout<<zup<<" ";
	}

//	cout<<1;
//	s.Draw();
	getch();
	
	
	return 0;
}
