#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>
#include<algorithm>

#define w 400
#define len 10
#define N 1000		//10
#define K1 1
#define K2 2			//0.1
//#define A 60
#define g 0
#define b 0.0		//0.01
#define e 0.7
using namespace std;


Screen s(w, w/1.2);
Screen gr(2*w, w+200);
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

float speed[N];

struct particle
{
	vect r, v, a;
	void show ()
	{
		//s.draw_circle_solid(r.x, r.y, 2, 0, 0, 200, 0);
		s.put_pixel(r.x/1.2, r.y/1.2, mod(v)*80, 255-mod(v)*80, 0);//draw_circle_solid//(r.x, r.y, 1, 0, mod(v)*100, 100, 0);
		//cout<<r.x<<" "<<r.y<<"\t";
		//Sleep(1);
	}

	void update_a (vect b1)
	{
		vect r1 = add(b1, mult(-1, r));
		vect f={0, 0};
		if (mod(r1)<120 && mod(r1)>1)
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
		if (r.x < 0)
		{
			v.x *= -e;
			r.x = 1;
		}
		if (r.y < 0)
		{
			v.y *= -e;
			r.y = 1;
		}
		a = {0, 0};
	}
	void save_speed(int i)
	{
		speed[i] = mod(v);
	}
};

particle drop[N]; 

void graph()
{
	int pcount=0, count=0, pos=0;
	float rng=0, inc=0.1;
	float scl=2;
	for (int i=0; i<N; i++)
	{
		if (speed[i] < rng + inc)
		{
			count++;
		}
		else
		{
			rng += inc;
			gr.draw_path(pos, pcount*scl+40, pos+10, count*scl+40, 245-count*scl, 0, count*scl);
			gr.draw_circle_solid(pos+10, count*scl+40, 3, 1, 245-count*scl, 0, count*scl);
			pcount = count;
			count=0;
			pos+=10;
		}
	}
}

int main()

{
	float nrg=0;
	for (int i=0; i<N; i++)
	{
		drop[i].r = {rand()%(w-2)+1, rand()%(w-2)+1};
		float th= float(rand()%628)/100.0;
		drop[i].v = {cos(th), sin(th)};//{float(rand()%200)/100-1, float(rand()%200)/100-1};
	}
	
		nrg=0;
	while(1)
	{
//		if (nrg!=0)
		for (int i=0; i<N; i++)
		{
			drop[i].show();
			//cout<<'a';
		}
//		if (nrg!=0)
		for (int i=0; i<N-1; i++)
		{
			for (int j=i+1; j<N; j++)
			{
				drop[i].update_a(drop[j].r);
				drop[j].update_a(drop[i].r);
			}
		}
//		if (nrg!=0)
		for (int i=0; i<N; i++)
		{
			drop[i].update_pos();
			drop[i].save_speed(i);
		}
		sort(speed, speed+N);
	//	for (int i=0; i<N; i++)
	//	{
	//		nrg+=speed[i]*speed[i];
	//	}
		graph();
	//	gr.draw_path(w-2, 60, w-2, 60+nrg/10, 200, 0, 0);
		gr.Draw();
		s.Draw();
		Sleep(1);
		gr.clear();
		s.clear();
//		if (nrg==0)
//		getch();
//		nrg=1;
	}
	return 0;
}

