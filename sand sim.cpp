#include<iostream>
#include<conio.h>
#include<render.h>

#define size 500

Screen s(size, size);

using namespace std;

//int heap[size];

struct ar
{
	int val;
	int R[size], G[size], B[size];
}; 
ar heap[size];

double r=100, g=190, b=20;
double vr, vg, vb;
int curr, curg, curb;
void update_col()
{
	vr += float(rand()%100-50)/1000000;//float(rand()%100-50)/1000;
	vb += float(rand()%100-50)/1000000;//float(rand()%100-50)/1000;
	vg += float(rand()%100-50)/1000000;//float(rand()%100-50)/1000;
	//vg += rand()%10-5;//float(rand()%100-50)/1000;
	//vb += rand()%10-5;//float(rand()%100-50)/1000;
	r+=vr;
	g+=vg;
	b+=vb;
	if (r>=255)
	{
		vr*=-0.9;
		r=254;
	}
	if (g>=255)
	{
		vg*=-0.9;
		g=254;
	}
	if (b>=255)
	{
		vb*=-0.9;
		b=254;
	}
	if (r<=0)
	{
		vr*=-0.9;
		r=1;
	}
	if (g<=0)
	{
		vg*=-0.9;
		g=1;
	}
	if (b<=0)
	{
		vb*=-0.9;
		b=1;
	}
	if (rand()%1000==1)
	{
		curr=int(r);
		curb=int(b);
		curg=int(g);
	}
//	cout<<r<<"\t"<<g<<"\t"<<b<<"\t";
}
struct particles
{
	float x, y;
	float vx, vy;
	int state=0;
	int R, G, B;	
	void update()
	{
		if (state==1)
		{
			y+=vy;
			x+=vx;
			vy-=0.01;
		}
	}
	void activate()
	{
		state=1;
		vx = float(rand()%100-50)/400;//float(rand()%100-50)/20;
		vy = float(rand()%100-50)/100;//float(rand()%100-50)/20;
		R=int(curr+rand()%20-10);//rand()%255;
		G=int(curg+rand()%20-10);//rand()%255;
		B=int(curb+rand()%20-10);//rand()%255;
			if (R>=255)
			{
				R=254;
			}
			if (G>=255)
			{
				G=254;
			}
			if (B>=255)
			{
				B=254;
			}
			if (R<=0)
			{
				R=1;
			}
			if (G<=0)
			{
				G=1;
			}
			if (B<=0)
			{
				B=1;
			}
	}
	
	void show()
	{
		if (state==1)
		s.put_pixel(x, y, R, G, B);
	}
	
	void check()
	{
		if (x<size && x>=0)
		if (heap[(int)x].val>y && state==1)
		{
			heap[(int)x].val++;
			heap[(int)x].R[heap[(int)x].val]=R;
			heap[(int)x].G[heap[(int)x].val]=G;
			heap[(int)x].B[heap[(int)x].val]=B;
			state=0;
		}
	}
};
int cursand;
particles sand[2*size];

POINT cursor()
{
	POINT m;
	if (GetCursorPos(&m));
	HWND hWnd;
	hWnd = GetConsoleWindow();
	if (ScreenToClient(hWnd, &m));	
	m.y=size-m.y;
	POINT p;
	p.x=rand()%size;
	p.y=rand()%size;
	return p;
}

void display()
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<heap[i].val; j++)
		s.put_pixel(i, j, heap[i].R[j], heap[i].G[j], heap[i].B[j]);
	}
}



void copy (ar& a, ar& b)
{
	a.R[a.val+1]=b.R[b.val];
	a.G[a.val+1]=b.G[b.val];
	a.B[a.val+1]=b.B[b.val];
}

int main()
{
	srand(100);
	cursand=0;
	POINT M;
	int cur;
	cur=rand()%size;
	
	update_col();
		curr=r;
		curb=b;
		curg=g;
	while (1)
	{
		M=cursor();
		if (cursand>=0&& !(M.x>=size || M.x<0 || M.y>=size || M.y<0)) 
		{
			if (heap[M.x].val<M.y)
			{
				for (int i=0; i<2; i++)
				{
					cursand++;
					if (cursand>2*size)
					cursand=0;
					sand[cursand].vx=float(rand()%100-50)/400;
					sand[cursand].vy=float(rand()%100-50)/100;
					sand[cursand].activate();
					sand[cursand].x=M.x;
					sand[cursand].y=M.y;
				}
		//		cout<<sand[cursand].x;
			}
		}
		
		if (cursand>=0)
		for (int i=0; i<2*size; i++)
		{
			sand[i].check();
			sand[i].update();
			sand[i].show();
		}
		
/*		cur=rand()%size;
		else
		cur = M.x;
		heap[cur+rand()%4-2]++;
*/		for (int i=1; i<size-1; i++)
		{
			if (heap[i].val>heap[i+1].val+1 || rand()%500==1)
			{
				copy(heap[i+1], heap[i]);
				heap[i].val--;
				heap[i+1].val++;
			/*	heap[i+1].R[heap[i+1].val]=R;
				heap[i+1].G[heap[i+1].val]=G;
				heap[i+1].B[heap[i+1].val]=B;
			*/
			}
			
			if (heap[i].val>heap[i-1].val+1 || rand()%500==1)
			{
				copy(heap[i-1], heap[i]);
				heap[i].val--;
				heap[i-1].val++;
				//heap[i-1].R[heap[i-1].val]=R;
				//heap[i-1].G[heap[i-1].val]=G;
				//heap[i-1].B[heap[i-1].val]=B;
			}
		}
		if (heap[0].val>heap[1].val+1 || rand()%500==1)
		{
		//	heap[0]--;
		//	heap[1]++;
			copy(heap[1], heap[0]);
			heap[0].val--;
			heap[1].val++;
		//	heap[1].R[heap[1].val]=R;
		//	heap[1].G[heap[1].val]=G;
		//	heap[1].B[heap[1].val]=B;
		}
		if (heap[size-1].val>heap[size-2].val+1 || rand()%500==1)
		{
		//	heap[size-1]--;
		//	heap[size-2]++;
			copy(heap[size-2], heap[size-1]);
			heap[size-1].val--;
			heap[size-2].val++;
		//	heap[size-2].R[heap[size-2].val]=R;
		//	heap[size-2].G[heap[size-2].val]=G;
		//	heap[size-2].B[heap[size-2].val]=B;
		}
		
		update_col();
		
		display();
		s.Draw();
//		Sleep(1);
		s.clear();
//		system("cls");
	}
	
	return 0;
}
