#include<iostream>
#include<conio.h>
#include<cmath>
#include<render.h>

#define size 400
#define fact 3
#define g (0.01*fact*fact)
#define P 60
#define stime 30
using namespace std;

Screen s(size, size);

int score=0;
int pscore = 0;
int streak=0;

struct vect
{
	float x, y;
};	
vect target = {size/2, size*4/5};

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


struct particles
{
	vect r, v, a;
	float R;
	void init(vect r_, vect v_, float R_)
	{
		v_ = add(v_, {float(rand()%100)/100 - 0.5, float(rand()%100)/100 -0.5});
		v=v_;
		R=R_;
		r_ = add(r_, {rand()%int(2*R) - R, rand()%int(2*R) - R});
		r=r_;
		R/=2;
	}
	void update()
	{
		if (R>0)
		{
			a = {0, -g};
			v = add(a, v);
			r = add(r, v);
			R-=0.1;
		}
	}
	void show (unsigned char G_, unsigned char  B_)
	{
		s.draw_circle_solid(r.x, r.y, R, 1, (255-G_)/5, G_/5, B_/5);
//		s.draw_circle_solid(100, 100, 100, 1, 255, 255, 255);
	}
};

vect mouse;
vect track[P];

void streak_count()
{
	static int time=0;
	if (score>pscore && time<=stime)
	{
		streak++;
	}
//	cout<<time<<endl;
	if (score>pscore)
	{
		time=0;
	}
	if(time>stime)
	{
		if (streak>0)
		score+=streak+1;
		streak=0;	
	}
	time++;
}

void cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	mouse.x=m.x;
	mouse.y=size - m.y;
}

struct fruit
{
	vect r, v, a;
	float R;
	unsigned char G_, B_;
	int state=0;
	int level;
	particles p[6];
	
	void update()
	{
		if (r.y>-R-1)
		{
			a = {0, -g};
			v = add(a, v);
			r = add(r, v);
		}
		else
		level = 0;
		
		if (state==0)
		{
			for (int i=0; i<6; i++)
			p[i].update();
		}
	}	
	void show ();	
	
//	void showp()
//	{
//	}
	void check(int &ps, int &s);
};


void fruit::check(int &ps, int &s)
{
	if (state==1)
	{
		int flag=0;
		if (!(track[1].x==track[0].x && track[1].y==track[0].y))
		for (int i=0; i<14; i++)
		{
			if (dist(track[i], r)<R+1)
			{
				flag =1;
				break;
			}
		}
		if (flag==1)
		{
			state=0;
			for (int i=0; i<6; i++)
			{
				p[i].init(r, v, R);
			}
//			ps=s;
			s++;
		}
	}
}
void fruit::show()
{
	if (state>0)
	s.draw_circle_solid(r.x, r.y, R, 0, (255-G_), G_, B_);
	else
	{
		for (int i=0; i<6; i++)
		p[i].show(G_, B_);
	}
}

void showpath()
{
	for (int i=0; i<P; i++)
	{
		s.draw_circle_solid(track[i].x, track[i].y, (P-i)/(P/3), 0, 255, 0, 255);
	}
}

fruit F[10]; 
fruit B[3];
int main()
{
	for (int i=0; i<10; i++)
	F[i].level=0;
	for (int i=0; i<10; i++)
	B[i].level=0;
	
	for (int i=0; i<P; i++)
	track[i]=mouse;
	
	
	float d=100;
	int count=0;
	while (1)
	{
		for (int i=0; i<10; i++)
		{
			if (F[i].level==0)
			{
				if (rand()%(int)d ==1)
				{
					F[i].level=1;
					int a = rand()%size;
					F[i].r = {a, -20};
					F[i].v = {float (size/2 - a)*1.4/size -0.4 +float(rand()%80)/100, 1.6 + float (rand()%90)/100};
					F[i].v = mult(fact, F[i].v);
					F[i].R = rand()%20 + 10;
					F[i].G_= rand()%255;
					F[i].B_= 0;
					F[i].state=1;
				}
			}
		}
		for (int i=0; i<10; i++)
		{
			F[i].show();
		}
		for (int i=0; i<10; i++)
		{
			F[i].update();
		}
		cursor();
		for (int i=0; i<10; i++)
		{
			F[i].check(pscore, score);
		}
		count++;
		if (count>30)
		{
			count=0;
			d*=0.999;
		}
		for (int i=P-1; i>0; i--)
		{
			track[i]=track[i-1];
		}
		track[0]=mouse;
		showpath();
		streak_count();
//		count=0;
	//	d*=0.999;
		for (int i=0; i<size/20; i++)
		cout<<endl;
		cout<<"score: "<<score<<endl<<"streak ";
		if (streak>0)
		{
			cout<<streak+1;
		}
		else
		cout<<streak;
		system("cls");
		s.Draw();
		s.clear();
		pscore=score;
//		Sleep(1);
	}
	return 0;
}
