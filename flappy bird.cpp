#include<iostream>
#include<conio.h>
#include<render.h>

#define g 1.4
#define K 3
#define w 400
#define f 10
#define size 100
#define wid 30
using namespace std;

Screen s(w, w);

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

struct point
{
	vect p, v, a;
	float r;
	int state=1;
	void show()
	{
		s.draw_circle_solid(p.x, p.y, r, 0, 100, 0, 0);
	}
	void update()
	{
		if (state==1)
		{
			a = {0, -g};
			v = add(v, a);
			p = add(p, v);
		}
	}
	void check()
	{
		unsigned char r_, g_, b;
		for (float i=0; i<6.2831; i+=0.02)
		{
			s.get_pixel(p.x+(20)*cos(i), p.y+(20)*sin(i), r_, g_, b);
			if (g_>10)
			{
				state=0;
			}
		}
		if (p.y<0)
		{
			state=0;
		}
	}
	void flap()
	{
		v.y = f;
	}
};
point bird;

struct pillar
{
	vect p;
	void set(int i)
	{
		p.y = rand()%250+75;
		p.x = (size+wid)*i+400;
	}
	int check()
	{
		return (p.x<0);
	}
	void update()
	{
		p.x-=2;
	}
	void show()
	{
		for (int i=-wid/2; i<wid/2; i++)
		{
			s.draw_path(p.x+i, w, p.x+i, p.y+size/2, 0, 100, 0);
			s.draw_path(p.x+i, 0, p.x+i, p.y-size/2, 0, 100, 0);
		}
	}
};
pillar block[K];

int main()
{
	bird.p.x = 150;
	bird.p.y = 150;
	bird.r=13;
	bird.show();
	s.Draw();
	s.clear();
	cout<<"press any key to continue";	
	int j;
	for (j=0; kbhit()==0; j++);
	srand(j);
	system("cls");
	int cont=1;
	while (cont==1)
	{
		bird.p.x = 150;
		bird.p.y = 150;
		bird.v = {0, 0};
		bird.r=13;
		for (int i=0; i<100; i++)
		{
			block[i].set(i);
		}
		cont=1;
		int score=0, lag=0;// lag2=0;
	//	int curb=0;
		bird.state=1;
		while (bird.state==1)
		{
			for (int i=0; i<100; i++)
			{
				block[i].update();
				block[i].show();
			}
			bird.show();
			bird.check();

			if (kbhit()!=0 && lag>2)
			{
				char a = getch();
				if (a==' ')
				bird.flap();
				lag=0;
				//cout<<0;
			}
			bird.update();
			if (bird.p.x>block[score].p.x)
			{
				score++;
				system("cls");
				for (int i=0; i<20; i++)
				cout<<"\n";
				cout<<score;
			}
			lag++;
			//lag2++;
			s.Draw();
			//Sleep(10);
			s.clear();
			for (int i=0; i<K; i++)
			{
				if (block[i].check())
				{
					block[i].set(K);
				}
			}
			
		}
		system("cls");
		cout<<"score: "<<score<<"\n";
		cout<<"continue ? (1/0)";
		cin>>cont;
	}
	return 0;
}
