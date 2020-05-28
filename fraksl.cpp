#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>

#define size1 1000
#define size2 500

using namespace std;

const int num=4;

int color=20;

Screen s(size1, size2);
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

struct object
{
	vect p1, p2, p3, p4;
	void show(int i)
	{
	//	cout<<'a';
	//	s.put_pixel(100, 100, 100, 100, 100);
	//	s.triangle
		s.triangle (p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, 0, i*255, i*255, i*255);
		s.triangle (p1.x, p1.y, p4.x, p4.y, p3.x, p3.y, 0, i*255, i*255, i*255);
	}
	void set(vect p1_, vect p2_, vect p3_, vect p4_)
	{
		p1=p1_;
		p2=p2_;
		p3=p3_;
		p4=p4_;
	}
};

vect transform (vect o1, vect o2, vect newo1, vect newo2, vect p)
{
	vect axis1, axis2;
	vect r1;
	axis1 = add(o2, mult(-1, o1));

	r1 = add(p, mult(-1, o1));
	axis2 = add(newo2, mult(-1, newo1));

	float len=mod(axis2)*mod(r1)/mod(axis1);

	float Tx1, Tx2, Tr;
	if (axis1.x!=0)
	Tx1=atan2(axis1.y, axis1.x);
	if (axis2.x!=0)
	Tx2=atan2(axis2.y, axis2.x);
	if (r1.x!=0)
	Tr=atan2(r1.y, r1.x);

	float T=Tr-Tx1+Tx2;
	vect q = add(newo1, mult(len, {cos(T), sin(T)}) );

	return q;
}


void recur(object a, object b, int lim, int col)
{
	if (lim>0)
	{
		object c;
		c.p1 = transform(a.p1, a.p2, b.p3, b.p4, b.p1);
		c.p2 = transform(a.p1, a.p2, b.p3, b.p4, b.p2);
		c.p3 = transform(a.p1, a.p2, b.p3, b.p4, b.p3);
		c.p4 = transform(a.p1, a.p2, b.p3, b.p4, b.p4);
		c.show(col);
		if (col==1)
		recur(b, c, lim-1, 0);
		else
		recur(b, c, lim-1, 1);
	}
}

void place (object &c, vect p_, int s1, int s2, float th)
{
	float alp = th + 3.141/2;
	vect p2 = add(p_, {s1*cos(th), s1*sin(th)});
	vect p3 = add(p2, {s2*cos(alp), s2*sin(alp)});
	vect p4 = add(p_, {s2*cos(alp), s2*sin(alp)});
	
	c.set(p_, p2, p3, p4);
}

int main()
{
	object a, b;
	a.set({0, 0}, {size1, 0}, {size1, size2}, {0, size1});
	//b.set({100, 100}, {300, 200}, {250, 300}, {50, 200});
	for (float th=0; th<1; th+=0.01)
	{
		place(b, {200,0}, 700, 350, th);
		
		a.show(1);
		b.show(0);
		recur(a, b, 20, 1);
		s.Draw();
		s.clear();
	}
		getch();
	return 0;
}
