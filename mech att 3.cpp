#include<iostream>
#include<conio.h>
#include<render.h>

#define size1 1000
#define size2 600
#define K 0.001
#define g 0.01
#define N 10
#define b 0.999
float R = 200;
float R2 = 290;
using namespace std;

Screen s(size1, size2);
Screen p(size1, size2);
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
	//	v = mult(b, v);
		r = add(r, v);
		
	}
	
	void check()
	{
		for (int i=0; i<1 ; i++)
		{
			vect dir = add( obs, mult(-1, r));
			if ( mod(dir) < R  ) 
			{
				float comp = dot(v, dir)/mod(dir);
				float e = float(rand()%50)/100.0;
				v = add(v, mult(-(1.1+e)*comp/mod(dir), dir));
				r=rp;
			}
			
			dir = add( r, mult(-1, obs));
			if ( mod(dir) > R2 && !(dir.y<-0.99*R2) ) 
			{
				float comp = dot(v, dir)/mod(dir);
				float e = float(rand()%100)/100.0;
				v = add(v, mult(-(1.1+e)*comp/mod(dir), dir));
				r=rp;
			}
	}
		
	}
	
	void checkp(vect r2)
	{
		vect dir=add(r, mult(-1, r2));
		if (mod(dir)>2)
		v = add(mult(K/mod(dir)/mod(dir)/mod(dir), dir), v);
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
		if (i==0)
		s.draw_path_2(r.x, r.y, rp.x, rp.y,  color, color, color);
		else
		s.draw_path_2(r.x, r.y, rp.x, rp.y,  color, 0, 0);
		
	//	if (color>3)
	//	color-=0.2;
		a = {0, 0};
	}
};

point part[N];
point part2[N];
int main()
{
	//srand(100);
/*	for (int i=0; i<N; i++)
	{
		part[i].r.x = size1/2 + 50 - rand()%100;
		part[i].r.y = size2;
		part[i].state = 0;
		part[i].color = 50;//rand()%70;
		part[i].v={0, -1.8};
	}
*/	
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
	
		for (int i=0; i<N; i++)
		{
			part[i].update();
			part[i].border();
		}
		for (int i=0; i<N; i++)
		{
			part[i].check();
		}
		for (int i=0; i<N-1; i++)
		{
			for(int j=i+1; j<N; j++)
			{
				part[i].checkp(part[j].r);
				part[j].checkp(part[i].r);
			}
		}
		for (int i=0; i<N; i++)
		{
			part[i].show();
			if (mod(part[i].v)<0.6)
			part[i].state = 1;
		}
	//	if (!(time%1000))
		for (int i=0; i<N; i++)
		{
			if (part[i].state == 1)
			{
				part[i].r.x = size1/2 + 50 - rand()%100;
				part[i].r.y = size2-30;
				part[i].state = 0;
				part[i].color = 100;//rand()%40;
				part[i].v = {float(rand()%100 - 50)/100, -1};
			}
		}
				
		
		
		
		s.Draw();
		s.clear();
		time++;
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
	for (int i=0; i<size1; i++)
		{
			for (int j=0; j<size2; j++)
			{
				unsigned char r_, g_, b_;
				s.get_pixel(i, j, r_, g_, b_);
				p.put_pixel(i, j, 255-r_, 255-g_, 255-b_);
				//s.put_pixel_2(i, j, 50, 50, 50);
			}
		}
	p.Draw();
	getch();
	getch();
	return 0;
}
