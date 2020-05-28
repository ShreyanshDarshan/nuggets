#include<iostream>
#include<conio.h>
#include<render.h>

#define size 800
#define N 400


// FORCE CONSTANTS

#define F 3		//2		1		1		0.1		0.1		5
#define p 0.04	//1.04	1.04	1.04	0		0		1.04
#define d 0.1	//0.1	0.1		0.1		0.01	0.01	0.01
#define q 1.04	//2.04	2.04	3.04	2.34	2.34	3.04
#define MIN 3	//3		3		3		3		3		3
#define MAX_V 3	//1		1		1		1		2		3

float max (float a, float b)
{
	return (a>b)?a:b;
}

using namespace std;

Screen s(size, size);

struct vect
{
	float x, y;
};

vect add(vect v1, vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

vect mult(float k, vect v)
{
	v.x *= k;
	v.y *= k;
	return v;
}

float mod(vect v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

float dist(vect r1, vect r2)
{
	return sqrt((r1.x-r2.x)*(r1.x-r2.x) + (r1.y-r2.y)*(r1.y-r2.y));
}

float dot (vect v1, vect v2)
{
	return v1.x*v2.x + v1.y*v2.y ;
}

struct pt
{
	vect r, v, a;
	int R, G, B;
	
	void update_r()
	{
		r=add(r, v);
	}
	
	void update_v(vect tar)
	{
		a={0, 0};
		if (dist(tar, r)>MIN)
		{
			float factor = F/pow(dist(tar, r), p+1);
			a = mult(factor, add(tar, mult(-1, r)));
			float drag = d*pow(mod(v), q-1);
			a = add(a, mult(-drag, v));
	//		a = mult(, a);
		}
		else
		{
	//		float factor = F/pow(MIN, p)/sqrt(dist(tar, r));
	//		a = add(a, mult(factor, add(tar, mult(-1, r))));
	//		float drag = d*pow(mod(v), (q-1)/2);
	//		a = add(a, mult(-drag, v));
	//		a = mult(, a);
		}
		v=add(v, a);
		if (mod(v)>MAX_V)
		{
			v=mult(MAX_V/mod(v), v);
		}
	}
	
	void show()
	{
	//	s.put_pixel(r.x, r.y, r_, 255-g_, b_);
		s.put_pixel(r.x, r.y, R, G, B);
	}
	
};

pt P[N];

POINT cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	m.y=size-m.y;
	return m;
}

int main()
{
	for (int i=0; i<N; i++)
	{
		P[i].R=255;
		P[i].G=(i/2)%255;
		P[i].r = {rand()%size, rand()%size};
		P[i].v={rand()%100 - 50,rand()%100 - 50 };
		P[i].v = mult(0.001, P[i].v); 
	}
	while(1)
	{
		POINT mouse = cursor();
		P[N-1].r.x = mouse.x;
		P[N-1].r.y = mouse.y;
		for (int i=0; i<N-1; i++)
		{
			P[i].update_v(P[i+1].r);
		}
		
		
		for (int i=0; i<N-1; i++)
		{
			P[i].update_r();
			P[i].show();
		}
		
		
		s.Draw();
	//	Sleep(1);
		s.fade();
//		cout<<mod(P[N-2].v);
	}
	return 0;
}
