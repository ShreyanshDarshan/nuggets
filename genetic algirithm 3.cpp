#include<iostream>
#include<conio.h>
#include<cmath>
#include<render.h>
#include<algorithm>

#define len 300
#define num 100
#define size 700
#define g 0.07
#define mut1 2
#define mut2 3
#define obnum 6
#define chosen 3

using namespace std;

Screen s(size, size);

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



struct obstacle
{
	public:
	vect r1, r2;
		
	void set(int x, int y, int l, int h)
	{
		r1 = { x - l/2, y - h/2};
		r2 = { x + l/2, y + h/2};
	}
	
} bar[obnum];


struct craft
{
	vect r, v, a;
	float fit;
	float fit2;
	float dna[len];
	int state=0;
	vect path[len];
	
	void show ()
	{
		s.draw_circle_solid(r.x, r.y, 3, 1, 50, 0, (size*2-1/fit)/20);
	}
	
	void update (int time)
	{
		if (state==0)
		{
			a = {cos(dna[time]), sin(dna[time]) - g};
			v = add (v, a);
			r = add (r, v);
			if (dist(target, r)<20)
			{
				state = 1;
			}
			for (int i=0; i<obnum; i++)
			{
				if (r.x > bar[i].r1.x && r.x < bar[i].r2.x && r.y > bar[i].r1.y && r.y < bar[i].r2.y)
				{
					state = -1;
				}
				if (r.x>size || r.x<0)
					state=-1;
				a={0, 0};
			}		
			
			path[time] = r;
			
			for (int k=0; k<time; k++)
			{
				//draw_path_2(path[k].x, path[k].y, path[k+1].x, path[k+1].y);
				s.put_pixel_2(path[k].x, path[k].y, 20, 20, 20);
			}
		}
		else if (state < 0)
		{
			path[time] = r;
			for (int k=0; k<time; k++)
			{
				//draw_path_2(path[k].x, path[k].y, path[k+1].x, path[k+1].y);
				s.put_pixel_2(path[k].x, path[k].y, 100, 0, 0);
			}
		}
		else if (state > 0)
		{
			path[time] = r;
			for (int k=0; k<time; k++)
			{
				//draw_path_2(path[k].x, path[k].y, path[k+1].x, path[k+1].y);
				s.put_pixel_2(path[k].x, path[k].y, 0, 100, 0);
			}
		}
	}
	
	void calc_fit(int time)
	{
		//int fit=0;
		
		if (state != -1)
		fit=1/dist(target, r);
		else
		fit=0;
		
		float fit2=0;
		for (int i=0; i<time; i++)
		{
			fit2 += dist(path[i], path[i+1]);
		}
		fit2=1/fit2;
		//cout<<1/sum<<"\t";
		//fit2 = sum;
		//fit=fit2;
		/*if (dist(target, r)>0)
		{
			fit = fit2;
		}
		fit=fit2;
		*/
	}

/*	void show_path(int time)
	{
			for (int k=0; k<time; i++)
		{
			//draw_path_2(path[k].x, path[k].y, path[k+1].x, path[k+1].y);
			s.put_pixel_2(path[k].x, path[k].y);
		}
	}
	
	void track_path(int time)
	{
		path[time] = r;
	}
*/
};

craft rocket[num];
craft selected[chosen];

void copy(craft &a, craft b)
{
	for (int i=0; i<len; i++)
	{
		a.dna[i] = b.dna[i];
	}
}

void mate (craft a, craft b, craft &child)
{
	int mid=rand()%len;
	
	for (int i=0; i<mid; i++)
	{
		//if (rand()%mut2)
			b.dna[i]=a.dna[i];
		//else
		//	b.dna[i]=float(rand()%628)/100;
	}
	copy(child, b);
}

void select()
{
	float bestfit[num];
	int index[chosen];
	for (int i=0; i<num; i++)
	{
		bestfit[i] = rocket[i].fit + rocket[i].fit2;
	}
	sort(bestfit, bestfit+num);
	
	for (int i=0; i<num; i++)
	{
		for (int j=0; j<chosen; j++)
		{
			if (rocket[i].fit == bestfit[num-1-j])
			{
				index[j] = i;
			}
		}
	}
	
	for (int i=0; i<chosen; i++)
	{
		copy(selected[i], rocket[index[i]]);
	}
/*	for (int i=0; i<5; i++)
	{
	//	cout<<index[i]<<"\n";
	}
*/
}

void breed()
{
	
	int k=0;
	for (int i=0; i<chosen-1; i++)
	{
		for (int j=i+1; j<chosen; j++)
		{
			mate(selected[i], selected[j], rocket[k]);
			k++;
		}
	}
	for (int i=0; i<len; i++)
	{
		rocket[num-1].dna[i] = float(rand()%628)/100;
	}
}

void mutation()
{
	for (int i=0; i<num; i++)
	{
		if (rand()%mut1==1)
		for (int j=0; j<len; j++)
		{
			if (rand()%mut2==1)
			rocket[i].dna[j]=float(rand()%628)/100;
		}
	}
}

void showtarget()
{
	s.draw_circle_hollow(target.x, target.y, 10, 1, 0 , 255, 0);
}

void showobs()
{
	for (int j=0; j<obnum; j++)
	{
		for (int i=bar[j].r1.x; i<=bar[j].r2.x; i++)
		{
			s.draw_path(i, bar[j].r1.y, i, bar[j].r2.y, 255, 0, 0);
		}
	}
}

int main()
{
	int seed;
	cout<<"enter random seed: ";
	cin>>seed;
	srand(seed);
	
	for (int i=0; i<obnum; i++)
	{
		bar[i].set( rand()%int(size/2) + 100, rand()%int(size/2) + 100 , 60, 30);
	}
	
	for (int i=0; i<num; i++)
	{
		rocket[i].r={size/2, size/4};
		rocket[i].v={0, 0};
		for (int j=0; j<len; j++)
		{
			rocket[i].dna[j] = float(rand()%628)/100;
		}
	}
	
	/*for (int i=1; i<num; i++)
	{
		int a = rand()%num;
		int b = rand()%num;
		int c = rand()%num;
		mate(rocket[a], rocket[b], rocket[c]);
	}
	*/
	while(1)
	{
		for (int time=0; time<len; time++)
		{
			for (int i=0; i<num; i++)
			{
				rocket[i].show();
				rocket[i].update(time);
				rocket[i].calc_fit(time);
				//if(i==5)
			//	{
				//	vect k={cos(rocket[i].dna[time]), sin(rocket[i].dna[time]) - g};
					//cout<<mod(rocket[i].a)<<" ";
				//	cout<<mod(k);
			//	}
			}
			showtarget();
			showobs();
			s.Draw();
		//	Sleep(1);
			s.clear();
		}
		
		/*for (int i=0; i<num; i++)
		{
			if (mod(rocket[i].v)==0)
			{
				for (int j=0; j<len; j++)
				{
				//	cout<<rocket[i].dna[j];
				}
				getch();
			}
		//	cout<<rocket[i].fit<<"\n";
		}
		*/	
		select();
		breed();
		mutation();//getch();
		for (int i=0; i<num; i++)
		{
			rocket[i].r={size/2, size/4};
			rocket[i].v={0, 0};
			rocket[i].state=0;
		}
	}
	return 0;
}
