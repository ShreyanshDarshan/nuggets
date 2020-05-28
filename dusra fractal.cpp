#include<iostream>
#include<conio.h>
#include<render.h>
#include<cmath>
//#include<stdlib.h>

#define size 600

using namespace std;

const int num=5;
int mode = 0;
int color=10;

Screen s(size, size);

struct vect
{
	float x, y;
};

void cursor(int &x, int &y, int& click)
{
	if (kbhit())
	{
		char n = getch();
		switch (n)
		{
			case ' ': click = 1; break;
			case 'w':
			case 'W': click = 2; break;
			case 's':
			case 'S': click = 3; break;
			case 'd':
			case 'D': click = 4; break;
			case 'a':
			case 'A': click = 5; break;
			case 'f':
			case 'F': click = 6; break;		
		}
	}
	else
	{
		click = 0;
	}
	POINT mouse;
	if (GetCursorPos(&mouse));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &mouse));	
	x=mouse.x;
	y=size - mouse.y;
	//cout<<x<<"\t"<<y;
	//s.draw_path(100, 100, 300, 300, 255, 0, 0);
}

vect hand[num];

vect transform (vect o1, vect o2, vect newo1, vect newo2, vect p)
{
	vect axis1, axis2;
	vect r1;
	axis1.x=o2.x-o1.x;
	axis1.y=o1.y-o2.y;

	r1.x=p.x-o1.x;
	r1.y=o1.y-p.y;


	axis2.x=newo2.x-newo1.x;
	axis2.y=newo1.y-newo2.y;

	float len1=sqrt ( axis1.x * axis1.x + axis1.y * axis1.y );
	float len2=sqrt ( axis2.x * axis2.x + axis2.y * axis2.y );
	float rad=sqrt ( r1.x * r1.x + r1.y * r1.y );
	float len=len2*rad/len1;

	float Tx1, Tx2, Tr;
	if (axis1.x!=0)
	Tx1=atan2(axis1.y,axis1.x);
	if (axis2.x!=0)
	Tx2=atan2(axis2.y,axis2.x);
	if (r1.x!=0)
	Tr=atan2(r1.y,r1.x);

	float T=Tr-Tx1+Tx2;
	vect q;
	q.x=newo1.x+len*cos(T);
	q.y=newo1.y-len*sin(T);

	return q;
}
int selected=-1;
int newclick, prevclick;

int check(int &xh, int &yh)
{
	int x, y;
	cursor(x, y, newclick);
	//cout<<selected;
	if (newclick==1 && prevclick==0)
	{
		if (selected == -1)
		{
			for (int i=0; i<num; i++)
			{
				float dist= sqrt( (hand[i].x-x)*(hand[i].x-x) + (hand[i].y-y)*(hand[i].y-y) );
				if (dist<=4)
				{
					selected=i;
					break;
				}
			}
		}
		else
		{
			selected=-1;
		}
	}
	xh=x;
	yh=y;
	//cout<<xh<<"\t"<<yh;
	prevclick=newclick;
	return selected;
}

void branch(float x1, float y1, float x2, float y2, int k, int lim)
{
	vect temp[num];
	temp[0].x=x1;
	temp[0].y=y1;
	temp[num-1].x=x2;
	temp[num-1].y=y2;
	for (int i=1; i<num-1; i++)
	{
		temp[i]=transform(hand[0], hand[num-1], temp[0], temp[num-1], hand[i]);
	}
	if (k<lim)
	{
		for (int i=0; i<num-1; i++)
		{
			branch(temp[i].x, temp[i].y, temp[i+1].x, temp[i+1].y, k+1, lim);
		}
	}
	else
	{
		if (mode == 1)
		{
			int x[num], y[num];
			for (int i=0; i<num; i++)
			{
				x[i]=temp[i].x;
				y[i]=temp[i].y;
			}
			s.polygon_solid(x, y, num, TRUE, color, 0, 0);
			//cout<<a;
		}
		else 
		{
			s.draw_path_2(x1, y1, x2, y2, 0, 0, color);
		}
	}
}

int main()
{
	for (int i=0; i<num; i++)
	{
		hand[i].x=40*i+20;
		hand[i].y=100;
	}
	hand[2].y=30;
	int snap;
	cout<<"SNAP? ";
	cin>>snap;
	vect p={170, 90};
	vect o1={100, 200};
	vect o2={400, 130};
	//callmouse();
	newclick=1;
	int lim=7;
	while (1)
	{
		//cout<<newclick;
		if (newclick!=0 || selected>-1)
		{
			Sleep(30);
			s.clear();


			//setcolor(1);
			branch(hand[0].x, hand[0].y, hand[num-1].x, hand[num-1].y, 0, lim);
			system("cls");

			for (int i=0; i<num; i++)
			{
				//setfillstyle(1, 2);
				//setcolor(2);
				s.draw_circle_solid(hand[i].x, hand[i].y, 4, 0, 100, 0);
				if (i>0)
				{
					s.draw_path(hand[i].x, hand[i].y, hand[i-1].x, hand[i-1].y, 0, 100, 0);
				}
			}
			s.Draw();
			//hand[2].y+=0.4;
			//cout<<newclick;
			switch (newclick)
			{
				case 2: lim++;	break;
				case 3: lim--;	break;
				case 4:	color+=5; break;
				case 5: color-=5; break;
				case 6: mode += pow(-1, mode); break;
//				cout<<"...";
			}
		}
		int x, y;
		int select=check(x, y);
		if (select!=-1)
		{
			if (snap==0)
			{
				//cout<<"a";
				hand[select].x=x;
				hand[select].y=y;
			}
			else
			{
				hand[select].x=(x/10)*10;
				hand[select].y=(y/10)*10;
			}
		}

		/*
		vect newo2={200, 70};
		vect newo1={100, 100};
		vect c=transform(o1, o2, newo1, newo2, p);
		line (o1.x, o1.y, o2.x, o2.y);
		line (newo1.x, newo1.y, newo2.x, newo2.y);
		putpixel(p.x, p.y, 2);
		putpixel(c.x, c.y, 1);
		o1.x+=0.7;
		o2.x-=0.7;
		*/
		//while (newclick!=1);
	}

	return 0;
//	close_graph();
}
