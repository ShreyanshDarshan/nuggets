#include<iostream>
#include<conio.h>
#include<cmath>
#include<render.h>

#define size 500
#define b1 0.986
#define b2 0.98
#define f1 0.06
#define f2 0.04
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
	return mod(add(r1, mult(-1, r2)));
}

float dot (vect v1, vect v2)
{
	return v1.x*v2.x + v1.y*v2.y ;
}


struct pen
{
	float th, w, l1, l2;
	vect v, r;
	float d;
	vect F;
	float T;
	
	void set(float th_, float w_, float l1_, float l2_, vect v_, vect r_, vect F_, float T_)
	{
		th=th_; w=w_; l1=l1_; l2=l2_;
		v=v_; 
		r=r_;
		F = F_;
		T = T_;
	}
	
	void apply_force(float x2, float y2)
	{
		float x1 = r.x-(l2-d)*cos(th);
		float y1 = r.y-(l2-d)*sin(th);
		F={x2-x1, y2-y1};
		F=mult(0.04, F);
		vect pos = {x1-r.x, y1-r.y};
		T = -(F.x*pos.y - F.y*pos.x)/400;
		v=add(v, F);
		w+=T;
	}
	
	void slider(int y)
	{
		d=y*(l1+l2)/size;
		s.draw_circle_solid(r.x-(l2-d)*cos(th), r.y-(l2-d)*sin(th), 3, 0, 0, 0, 200);
	}
	
	void update_v()
	{
		if (fabs(w)>2*f1)
		w-=fabs(w)*f1/w;
		else
		w*=b1;
		if (mod(v)>2*f2)
		v=add(mult(-f2/mod(v), v), v);
		else
		v=mult(b2, v);
//		cout<<w<<"\t"<<mod(v);
	}
	
	void update_r()
	{
		th+=w;
		r=add(r, v);
	}
	
	void lock(int x, int y)
	{
		s.draw_circle_solid(r.x-(l2-d)*cos(th), r.y-(l2-d)*sin(th), 3, 0, 0, 200, 0);
		s.draw_path(r.x-(l2-d)*cos(th), r.y-(l2-d)*sin(th), x, y, 100, 100, 100);
	}
	
	void show(int R, int G, int B)
	{
		s.draw_path(r.x+l1*cos(th), r.y+l1*sin(th), r.x-l2*cos(th), r.y-l2*sin(th), R,G,B);
		s.draw_circle_solid(r.x, r.y, 3, 0, R,G,B);
	}
	
	bool check(pen &p)
	{
	//	float dx =cos(th), dy =sin(th);
		float val1 = sin(th)*(p.r.x + p.l1*cos(p.th) - r.x) - cos(th)*(p.r.y + p.l1*sin(p.th) - r.y);
		float val2 = sin(th)*(p.r.x - p.l2*cos(p.th) - r.x) - cos(th)*(p.r.y - p.l2*sin(p.th) - r.y);
	//	cout<<((val1*val2) <= 0)<<"\t";
		return (val1*val2) <= 0;
	}
	
	
};

void separate(pen &a, pen &b)
{
	/*
	float th1=a.th, th2=b.th;// th_1=a.th, th_2=b.th;
	int i=0, j=0;
	float sp = 0.01;
	for (i=0; a.check(b) && b.check(a); i++)
	{
		a.th-=sp; b.th+=sp;
	}
	for (j=0; a.check(b) && b.check(a); j++)
	{
		a.th+=sp; b.th-=sp;
	}
	if (i<j)
	{
		a.th=th1;
		b.th=th2;
		a.th-=i*sp;
		b.th+=i*sp;
	}
	*/
	
	float t= a.th+b.th;
	a.th=t/2;
	b.th=t/2;
}

void collide(pen &a, pen &b)
{
	float w;
	w = (a.w+b.w)/2;
	a.w = b.w = w;
	vect v = add(a.v, b.v);
	v= mult(1/2, v);
	a.v =v;
	b.v=v;
}

POINT cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	POINT mouse;
	mouse.x=m.x;
	mouse.y=size - m.y;
	return mouse;
}

int main()
{
	vect a={4, 2}, b={40, 100};
	pen p1, p2;
	int flag=0;
	int turn =0;
	p1.set(1, 1, 50, 30, a, b, {0, 0}, 0);
	p2.set(1.6, 0.2, 50, 30, {2, 4}, {100, 100}, {0, 1}, 0);
	while (1)
	{
		if (flag==0)
		{
			p2.update_v();
			p2.update_r();
			p1.update_v();
			p1.update_r();
		}
		p2.show(200, 200, 0);
		p1.show(0, 200, 200);
		if (p1.check(p2) && p2.check(p1))
		{
		//	char a = getch();
			collide(p1, p2);
			separate(p1, p2);
		}
	//	cout<<endl;
		
		if (mod(p1.v)<0.01 && mod(p2.v)<0.01 && flag==0 && fabs(p1.w)<0.002 && fabs(p2.w)<0.002)
		{
			flag=1;
		}
		if (flag==1)
		{
			if (turn%2==0)
			p1.slider(cursor().y);
			else
			p2.slider(cursor().y);
			
			if (kbhit())
			{
				char a=getch();
				flag=2;
			}
		}
		if (flag==2)
		{
			if (turn%2==0)
			p1.lock(cursor().x, cursor().y);
			else
			p2.lock(cursor().x, cursor().y);
		}
		if (flag==2 && kbhit())
		{
			char a = getch();
//			p1.apply_force(p1.r.x, p1.r.y, cursor().x, cursor().y);
			if (turn%2==0)
			p1.apply_force(cursor().x, cursor().y);
			else
			p2.apply_force(cursor().x, cursor().y);
			
			turn++;
			flag=0;
		}
		s.Draw();
		s.clear();
		Sleep(1);
	}
	return 0;
}
