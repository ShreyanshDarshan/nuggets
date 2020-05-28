#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>

#define w 600
#define N 30
#define h 500
#define K 0.2
#define A 60
#define g 0.1
#define b 0.2
using namespace std;

Screen s(w, h);

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
	return mod(add(r1, mult(-1, r2)));
}

struct body
{
	vect r, v, a;
	//body *p1, *p2;
	void show (int x, int y)
	{
	//	s.draw_circle_solid(r.x, r.y, 2, 0, 0, 200, 0);
		s.draw_path(x, y, r.x, r.y, 0, 200, 0);
	}
	void update (float a1, float a2)
	{
		float f = K*(a1 + a2 - 2*r.y);
		a = {0, f - g};
		v = add (v, a);
		if (mod(v)>5)
		{
			v = mult(5/mod(v), v);
		}
		v = add(v, mult(-b, v));
		r = add (r, v);
	}
};

body spring[N];

int main()
{
	for (int i=0; i<N; i++)
	{
		spring[i].r = {w*(i+1)/N, h/2};
		spring[i].v = {0, 0};
	}
	
	float time = 0;
	srand(100);
	while (1)
	{
		if (time>6.28 && time<50)
		spring[0].r.y = h/2 + A*sin(time); 
		for (int i=1; i<N-1; i++)
		{
			spring[i].update(spring[i-1].r.y, spring[i+1].r.y);
			spring[i].show(spring[i-1].r.x, spring[i-1].r.y);
		}
		spring[N-1].show(spring[N-2].r.x, spring[N-2].r.y);
		//spring[0].update(spring[0].r.y, spring[1].r.y);
		s.Draw();
		Sleep(1);
		s.clear();
		time+=0.1;
	}
	return 0;
}
