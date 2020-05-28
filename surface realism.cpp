
#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>

#define strn 0.7
#define N 100
#define size 100
#define zup 1000
#define mu 1.4
#define K 0.4
#define b 0.97
#define d 600
#define fac 10
using namespace std;

Screen s(fac*size, fac*size);

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
		if (z>=0)
		s.draw_circle_solid(x*size/N, y*size/N, 1, 0, 0, 0, int(1060*z));
		else
		s.draw_circle_solid(x*size/N, y*size/N, 1, 0, fabs(int(1060*z)), 0, 0);
	}	
	void update_v(surface &t)
	{
		v+=(t.z - z)*K;
	}
	void update_pos()
	{
		v-=K*z;
		if (fabs(v)>1)
		{
			v=v*1/fabs(v);
		}
		v*=b;
		z+=v;
	}
} drop[N][N], nul;


struct vect
{
	float x, y, z;
};	


vect add(vect v1, vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

vect mult(float k, vect v)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
	return v;
}

float mod(vect v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float dist(vect r1, vect r2)
{
	return mod(add(r1, mult(-1, r2)));
}

float dot(vect v1, vect v2)
{
	return v1.x*v2.x + v1.z*v2.z + v1.y*v2.y;
}

vect cross(vect v1, vect v2)
{
	return {v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v2.z*v1.x, v1.x*v2.y - v2.x*v1.y};
}

POINT cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	m.y=fac*size-m.y;
//	POINT p;
//	p.x=rand()%size;
//	p.y=rand()%size;
	return m;
}
float time=0;
vect f(float x, float y)
{
	int i=x*N/size;
	int j=y*N/size;
	vect v1, v2, n;
	if (i>1 && i<N-1 && j>1 && j<N-1)
	{
		if (i%2==0)
		{
			v1={1, 0, strn*(drop[i+1][j].z-drop[i][j].z)};
			v2={0, 1, strn*(drop[i][j+1].z-drop[i][j].z)};
			n=cross(v1, v2);
		}
		else
		{
			v1={1, 0, strn*(drop[i+1][j].z-drop[i][j].z)};
			v2={0, -1, strn*(drop[i][j-1].z-drop[i][j].z)};
			n=cross(v2, v1);
		}
	}
	else
	n={0, 0, 1};
	
	return mult(1/mod(n), n);
}

/*vect g(float x, float y, float tx, float ty)
{
	x-=tx;
	y-=ty;
//	vect n={x*exp((-x*x -y*y)/4000)/200, y*exp((-x*x -y*y)/4000)/200, 1};
//	vect n={x/300, y/300, 1};
	return mult(1/mod(n), n);
}
*/
void see(float &x_, float &y_, float x, float y)
{
	vect inc={size/2-x, size/2-y, zup};
	inc = mult(1/mod(inc), inc);
	float th=acos(dot(inc, f(x, y)));
	float al=asin(sin(th)/mu);
	vect dir = mult(dot(inc, f(x, y)), f(x, y)); //dir becomes component along normal
//	cout<<f(x, y).x;
	vect comp = dir;  // comp ""
	dir= add(inc, mult(-1, dir)); //dir becomes component perpendicular to normal
	dir = mult(mod(comp)*tan(al)/mod(dir), dir); // dir becomes required component
	
	vect inc2 = add(dir, comp);  // inc2 becomes new incident ray
	
/*	inc2 = mult(1/mod(inc2), inc2);
//	cout<<inc2.x;
	float th2=acos(dot(inc2, g(x, y, t)));
	float al2=asin(sin(th2)/mu);
	vect dir2 = mult(dot(inc2, g(x, y, t)), g(x, y, t)); //dir becomes component along normal
	vect comp2 = dir2;  // comp ""
	dir2= add(inc2, mult(-1, dir2)); //dir becomes component perpendicular to normal
	dir2 = mult(mod(comp2)*tan(al2)/mod(dir2), dir2); // dir becomes required component
	
	inc2 = add(comp2, dir2);
*/
	float L = -d/inc2.z;
	x_=x+L*inc2.x;
	//cout<<inc2.x;
	y_=y+L*inc2.y;

}

void display(int x, int y)
{
	float x_, y_;
	see(x_, y_, x, y);//cursor().x/fac, cursor().y/fac);
//	if (x_>0 && x_<size && y_>0 && y_<size)
	{
	//	if (!((int(x_)%30)==0 || (int(y_)%30)==0))
		for (int k=0; k<fac; k++)
		for (int l=0; l<fac; l++)
		s.put_pixel(x*fac+k, y*fac+l, (int(x_))*2 ,0, (int(y_))*2  );
	}
}


int main()
{
//	cout<<2;
//	getch();
int t;//-size;
	while (!kbhit())
	{
		
		time+=0.1;
		POINT P=cursor();
		P.x/=fac;
		P.y/=fac;
		if (P.x<size && P.y<size && P.x>0 && P.y>0)
		drop[int(P.x*N/size)][int(P.y*N/size)].z=-0.6;
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
//				if ((float(i)==0.41*N && float(j)==1) || (float(i)==0.59*N && float(j)==1))
//				{
//					drop[i][j].z=5*sin(0.6*time);		
//				}
//				else
				{
					drop[i][j].update_pos();
				}
		//		drop[i][j].show();
		//		drop[i][j].update_pos();
		//		drop[i][j].show();
			}
		}
		for (int i=0; i<size; i++)
		{
			for (int j=0; j<size; j++)
			{
				display(i, j);
			//	s.put_pixel(i, j, 100, 0, 0);
			}
		}
		
		
/*		for (float i=-size/2; i<size/2; i++)
		{
			s.put_pixel(i+size/2, size+20+10*exp((-i*i)/4000), 100, 100, 100);
		}
*/		s.Draw();
		s.clear();
	}

//	cout<<1;
//	s.Draw();
	getch();
	
	
	return 0;
}
