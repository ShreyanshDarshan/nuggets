#include<iostream>
#include<conio.h>
#include<render.h>

#define size1 1000
#define size2 600

#define g 0.007
#define N 40

float R = 60;

using namespace std;

Screen s(size1, size2);

struct vect
{
	float x, y;
};

vect obs = {size1/2, size2/2};

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

float dot (vect v1, vect v2)
{
	return v1.x*v2.x + v1.y*v2.y ;
}

struct point
{
	vect r, rp, v, a;
	float color, state;
	void update()
	{
		rp = r;
		a = add(a, {0, -g});
		v = add(v, a);
		r = add(r, v);
	}
	
	void check()
	{
		vect dir = add( obs, mult(-1, r));
		if ( mod(dir) < R  ) 
		{
			float comp = dot(v, dir)/mod(dir);
			float e = float(rand()%50)/100.0;
			v = add(v, mult(-(1.1+e)*comp/mod(dir), dir));
			r=rp;
		}
	}
	
	void border()
	{
		if (r.x>size1)
		{
			state = 1;
		}
		if (r.y>size2)
		{
			state = 1;
		}
		if (r.x<0)
		{
			state = 1;
		}
		if (r.y<0)
		{
			state = 1;
		}
	}
	
	void show(int i=0)
	{
		if (i==1)
		s.draw_path_2(r.x, r.y, rp.x, rp.y,  0, 0, color);
		else
		s.draw_path_2(r.x, r.y, rp.x, rp.y,  color, 0, 0);
		
		if (color>3)
		color-=0.2;
		a = {0, 0};
	}
};

point part[N];
point part2[N];
int main()
{
	for (int i=0; i<N; i++)
	{
		part[i].r.x = size1/2 + 50 - rand()%100;
		part[i].r.y = size2;
		part[i].state = 0;
		part[i].color = rand()%70;
		part[i].v={0, -1.8};
	}
	
/*	for (int i=0; i<size1; i++)
	{
		for (int j=0; j<size2; j++)
		{
			s.put_pixel(i, j, 255, 255, 255);
		}
	}
*/	int time=0;
	while (!kbhit())
	{
		time++;
		for (int i=0; i<N; i++)
		{
			part[i].update();
			part[i].border();
		}
		for (int i=0; i<N; i++)
		{
			part[i].check();
		}
		for (int i=0; i<N; i++)
		{
			part[i].show();
		}
		
		for (int i=0; i<N; i++)
		{
			if (part[i].state == 1)
			{
				part[i].r.x = size1/2 + 50 - rand()%100;
				part[i].r.y = size2;
				part[i].state = 0;
				part[i].color = rand()%70;
				part[i].v = {float(rand()%100 - 50)/4000, -1};
			}
		}
		
		
		
		for (int i=0; i<N; i++)
		{
			part2[i].update();
			part2[i].border();
		}
		for (int i=0; i<N; i++)
		{
			part2[i].show(1);
		}
		for (int i=0; i<N; i++)
		{
			part2[i].check();
		}
		
		for (int i=0; i<N; i++)
		{
			if (part2[i].state == 1)
			{
				part2[i].r.y = size2 - rand()%100;
				part2[i].r.x = 0;
				part2[i].state = 0;
				part2[i].color = rand()%70;
				part2[i].v = {2.7, -float(rand()%50)/4000};
			}
		}
	//	s.Draw();
		/*
		if (time==100)
		{
			for (int i=0; i<size1; i++)
			{
				for (int j=0; j<size2; j++)
				{
					unsigned char r_, g_, b_, d=1;
					s.get_pixel(i, j, r_, g_, b_);
					if (b_>d)
					s.put_pixel(i, j, r_, g_, b_-d);
				}
			}		
			time=0;
		}
		*/
//		Sleep(1);
//		R+=0.01;
	}
	getch();
	getch();
	return 0;
}
