#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>

#define size 600	//600
#define N 200		//200
#define K 0.1		//0.1	//3
#define b 0.99		//0.99
#define sp 0.77		//0.77		//0.077

Screen s(size, size);

using namespace std;

struct vect2
{
	float x, y, z;
};	


vect2 add(vect2 v1, vect2 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

vect2 mult(float k, vect2 v)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
	return v;
}

float mod(vect2 v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float dist(vect2 r1, vect2 r2)
{
	return mod(add(r1, mult(-1, r2)));
}

float dot(vect2 v1, vect2 v2)
{
	return v1.x*v2.x + v1.z*v2.z + v1.y*v2.y;
}


struct surface
{
	int x, y;
	float z;
	float v;
	void set(int i, int j)
	{
		x=i;
		y=j;		
		z=0;
		v=0;
	}
	void show()
	{
		if (int(1060*z)>=0)
	//	s.draw_circle_solid(x*size/N, y*size/N, 1, 0, 0, 0, int(1060*z));
		if (int(1060*z)>=255)
		s.put_pixel_2(x*size/N, y*size/N, 255, 255, 0);
		else
		s.put_pixel_2(x*size/N, y*size/N, int(1060*z),  int(1060*z), 0);
		else
	//	s.draw_circle_solid(x*size/N, y*size/N, 1, 0, fabs(int(1060*z)), 0, 0);
		if (int(1060*z)<=-255)
		s.put_pixel_2(x*size/N, y*size/N, 255, 0, 0);
		else
		s.put_pixel_2(x*size/N, y*size/N, fabs(int(1060*z)), 0, 0);
	}	
	void update_v(surface &t)
	{
		v+=sp*(t.z - z)*K;
	}
	void update_pos()
	{
		v-=sp*K*z;
		if (v*v>sp*sp*4)
		{
			v=sp*2*(v>0?1:-1);
		}
		v*=b;
		z+=v;
	}
} drop[N][N], nul;

POINT cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	m.y=size-m.y;
//	POINT p;
//	p.x=rand()%size;
//	p.y=rand()%size;
	return m;
}

void amp(int j)
{
	static float max[N];
	for (int i=0; i<N; i++)
	{
		if (drop[i][j].z>max[i])
		max[i]=drop[i][j].z;
	}
	for(int i=0; i<N; i++)
	{
	//	s.put_pixel(i*size/N, j*size/N+max[i]*max[i]*10000, 0, 100, 0);
		s.put_pixel(i*size/N, j*size/N+drop[i][j].z*1000, 0, 100, 0);
	}
}

int main()
{
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			drop[i][j].set(i, j);
		}
	}
	
//	drop[N/2][N/2].z=1.3;
	
	nul.set(-1, -1);
	
	float t=0;
	
	while(1)
	{	
		t+=0.3;
		int x, y;
		x=cursor().x;
		y=cursor().y;
		if (x<size && y<size && x>0 && y>0)
		drop[int(N*x/size)][int(N*y/size)].z=-1;
		
		for (int i=1; i<N-1; i++)
		{
			for (int j=1; j<N-1; j++)
			{
				drop[i][j].update_v(drop[i-1][j]);
				drop[i][j].update_v(drop[i+1][j]);
				drop[i][j].update_v(drop[i][j-1]);
				drop[i][j].update_v(drop[i][j+1]);
		//		if (i==N/2)
			}
		}
		
		for (int i=0; i<N; i++)
		{
			for (int j=0; j<N; j++)
			{
				if ((float(i)==0.41*N && float(j)==1) || (float(i)==0.59*N && float(j)==1))
				{
					drop[i][j].z=50*sin(1.6*t);		
				}
				else
				{
					drop[i][j].update_pos();
				}
				drop[i][j].show();
			}
		}
		amp(100);
		s.Draw();	
		s.clear();
//		cout<<drop[N/2][N/2].z;
//		getch();
	}
	
	return 0;
}
