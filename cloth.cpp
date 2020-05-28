#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>

#define w 800
#define len 10
#define N 40		//10
#define K 0.3			//0.1
#define A 60
#define g 0.001
#define b 0.006		//0.01
using namespace std;

Screen s(w, w);

float wind = 0.01;
float time = 0;

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

int click=0, pclick=0, nclick=0;
int cursor(float &x, float &y)
{
//	int val=0;
	if (kbhit())
	{
		char n = getch();
		if (n==' ')
		{
			nclick=1;
		//	click += pow(-1, click);
		}
	}
	else
	{
		//click = 0;
		nclick=0;
	}
	if ((nclick==1 && pclick==0))
	{
		click += pow(-1, click);
		//cout<<pclick<<nclick<<"a \t";
	}
	POINT mouse;
	if (GetCursorPos(&mouse));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &mouse));	
	x=mouse.x;
	y= w - mouse.y;
	return nclick;
	//cout<<x<<"\t"<<y;
	//s.draw_path(100, 100, 300, 300, 255, 0, 0);
}


struct body
{
	vect r, v, a;
	//body *p1, *p2;
	void show (vect a1 , vect a2 )
	{
	//	s.draw_circle_solid(r.x, r.y, 2, 0, 0, 200, 0);
		s.draw_path_2(a1.x, a1.y, r.x, r.y, 0, 70, 0);
		s.draw_path_2(a2.x, a2.y, r.x, r.y, 0, 70, 0);
	}
	void update_a (int i, vect a1, vect a2, vect a3, vect a4)
	{
		/*float f1 = K*(a1.y + a2.y - 2*r.y);
		float f2 = K*(a1.x + a2.x - 2*r.x);
		float g1 = K*(b1.y + b2.y - 2*r.y);
		float g2 = K*(b1.x + b2.x - 2*r.x);
		*/
		vect f={0, 0}, r1 = add(r, mult(-1, a1)), r2 = add(r, mult(-1, a2)), r3 = add(r, mult(-1, a3)), r4 = add(r, mult(-1, a4)) ;
		//	float len =  20;
	//	if (p1 != &trash);
			f = add(mult((len - mod(r1))*K/mod(r1), r1), f);
	//	if (p2 != &trash);
			f = add(mult((len - mod(r2))*K/mod(r2), r2), f);
			if (a4.x!=r.x && a4.y!=r.y)
			f = add(mult((len - mod(r4))*K/mod(r4), r4), f);
			if (a3.x!=r.x && a3.y!=r.y)
			f = add(mult((len - mod(r3))*K/mod(r3), r3), f);
		//a = add(f, {wind+0.02*sin((time+i)/10), -g+0.01*sin((time+i)/10)});
		a = add(f, {0, -g});
			
	}
	void update_pos()
	{
		v = add (v, a);
		if (mod(v)>5)
		{
			v = mult(5/mod(v), v);
		}
		v = add(v, mult(-b, v));
		r = add (r, v);
		
	}
};

body spring[N][N];

int main()
{
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			spring[i][j].r = {len*(i+1), w - len*(j+1)};
			spring[i][j].v = {0, 0};
		}
	}
//	cout<<"hello";
	
	srand(100);
	vect mouse;
	int selecti, selectj;
	while (1)
	{
		//if (time<900)
		//spring[N-1][N-1].r.x = time; 
		cursor(mouse.x, mouse.y);
		if (click==1)
		{
			if (pclick==0 && nclick==1)
			{
				for (int i=0; i<N; i++)
				{
					for (int j=0; j<N; j++)
					{
						if (dist(mouse, spring[i][j].r)<10)
						{
							selecti=i;
							selectj=j;
							break;
						}
					}
				}
			}	
		}
		pclick=nclick;
		for (int k=0; k<4; k++)
		{
			for (int i=1; i<N-1; i++)
			{
				for (int j=1; j<N-1; j++)
				{
					spring[i][j].update_a(i, spring[i-1][j].r, spring[i+1][j].r, spring[i][j-1].r, spring[i][j+1].r);
				}
			//	spring[i].show(spring[i-1].r.x, spring[i-1].r.y);
			}
			for (int i=1; i<N-1; i++)
			{
				spring[i][0].update_a(i, spring[i-1][0].r, spring[i+1][0].r, spring[i][1].r, spring[i][0].r);
			}
			/*for (int i=1; i<N-1; i++)
			{
				spring[0][i].update_a(spring[0][i-1].r, spring[0][i+1].r, spring[1][i].r, spring[0][i].r);
			}
	*/
			for (int i=1; i<N-1; i++)
			{
				spring[N-1][i].update_a(N-1, spring[N-1][i-1].r, spring[N-1][i+1].r, spring[N-2][i].r, spring[N-1][i].r);
			}
			for (int i=1; i<N-1; i++)
			{
				spring[i][N-1].update_a(i, spring[i-1][N-1].r, spring[i+1][N-1].r, spring[i][N-2].r, spring[i][N-1].r);
			}
			//spring[0][0].update_a(0, spring[1][0].r, spring[0][1].r, spring[0][0].r, spring[0][0].r);
			//spring[N-1][0].update_a(N-1, spring[N-1][1].r, spring[N-2][0].r, spring[N-1][0].r, spring[N-1][0].r);
			//spring[0][N-1].update_a(0, spring[1][N-1].r, spring[0][N-2].r, spring[0][N-1].r, spring[0][N-1].r);
			//spring[N-1][N-1].update_a(N-1, spring[N-1][N-2].r, spring[N-2][N-1].r, spring[N-1][N-1].r, spring[N-1][N-1].r);
		
			for (int i=0; i<N; i++)
			{
				for (int j=0; j<N; j++)
				{
					spring[i][j].update_pos();
				//	spring[i][j].show(spring[i+1][j].r, spring[i][j+1].r);
				}
			}
		}
		if (click==1)
		{
			spring[selecti][selectj].r=mouse;
		}
		//cout<<click;
		for (int i=0; i<N-1; i++)
		{
			for (int j=0; j<N-1; j++)
			{
			//	spring[i][j].update_pos();
				spring[i][j].show(spring[i+1][j].r, spring[i][j+1].r);
			}
		}
		
		for (int i=0; i<N-1; i++)
		{
			spring[i][N-1].show(spring[i+1][N-1].r, spring[i+1][N-1].r);
		}
		for (int i=0; i<N-1; i++)
		{
			spring[N-1][i].show(spring[N-1][i+1].r, spring[N-1][i+1].r);
		}
		//spring[N-1][N-1].show();
		
		//spring[0].update(spring[0].r.y, spring[1].r.y);
		s.Draw();
		Sleep(1);
		s.clear();
		time+= 1.1;
	}
	
	return 0;
}
