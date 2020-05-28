#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>
//#include<algorithm>

#define w 400
#define len 10
#define N 600		//10
#define K1 2
#define K2 3			//0.1
//#define A 60
#define g 0.000000001
#define b 0.02		//0.01
#define e 0.3
using namespace std;

Screen s(w, w);

float A=10, time=0;

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

//float speed[N];

struct particle
{
	vect r, v, a;
	void show ()
	{
		//s.draw_circle_solid(r.x, r.y, 2, 0, 0, 200, 0);
		s.put_pixel(r.x, r.y, 0, 200, 0);
		//cout<<r.x<<" "<<r.y<<"\t";
		//Sleep(1);
	}

	void update_a (vect b1)
	{
		vect r1 = add(b1, mult(-1, r));
		vect f;
		if (mod(r1)>0)
		{
			f = mult (-K2/pow(mod(r1), 3), r1);
		/*	if (mod(r1)<10)
			{
				vect t = (10/mod(r1), r1);
				f = mult(K1, add(r1, mult(-1, t)));
			//	f = mult (-K1/pow(mod(r1), 3), r1);
			}
			else
			{
				f = mult (K2/pow(mod(r1), 3), r1);
			}
		*/
		}
	
		a = add (a, f);
	}
	void update_pos()
	{
		a = add(a, {0, -g});
		v = add (v, a);
		if (mod(v)>5)
		{
			v = mult(5/mod(v), v);
		}
		v = add(v, mult(-b, v));
		r = add (r, v);
		if (r.x > w)
		{
			v.x *= -e;
			r.x = w;
		}
		if (r.y > w)
		{
			v.y *= -e;
			r.y = w;
		}
		if (r.x < A+A*sin(time))
		{
			v.x *= -e;
			v.x += 5*cos(time);
			r.x = A+A*sin(time) + 1;
		}
		if (r.y < 0)
		{
			v.y *= -e;
			r.y = 1;
		}
		a = {0, 0};
	}
/*	void save_speed(int i)
	{
		speed[i] = mod(v);
	}
*/
};


particle drop[N]; 

int main()

{
	for (int i=0; i<N; i++)
	{
		drop[i].r = {rand()%w, rand()%w};
	}
	
	while(1)
	{
	//	if (time>100)
		time+=0.3;
		for (int i=0; i<N; i++)
		{
			drop[i].show();
			//cout<<'a';
		}
		for (int i=0; i<N-1; i++)
		{
			for (int j=i+1; j<N; j++)
			{
				drop[i].update_a(drop[j].r);
				drop[j].update_a(drop[i].r);
			}
		}
		for (int i=0; i<N; i++)
		{
			drop[i].update_pos();
		}
		s.Draw();
		Sleep(1);
		s.clear();
		
	}
	return 0;	
}

