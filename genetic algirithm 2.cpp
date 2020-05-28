#include<iostream>
#include<conio.h>
#include<cmath>
#include<render.h>
#include<algorithm>

#define len 200
#define num 11
#define size 400
#define g 0.07
#define mut1 5
#define mut2 4

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

struct craft
{
	vect r, v, a;
	float fit;
	float dna[len];
	int state=0;
	
	void show ()
	{
	//	cout<<"aaaaa"<<(fit*40000)<<"\t";
	//	getch();
		s.draw_circle_solid(r.x, r.y, 10, (size*2-1/fit)/1.8, 0, 200);
	}
	
	void update (int time)
	{
		if (state==0)
		{
			a = {cos(dna[time]), sin(dna[time]) - g};
	//		a = mult(2, a);
			v = add (v, a);
			r = add (r, v);
			if (dist(target, r)<20)
			{
				state = 1;
			}
			a={0, 0};
		}
	}
	
	void calc_fit()
	{
		fit=1/dist(target, r);
	}
};

craft rocket[num];
craft selected[5];

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
	int index[5];
	for (int i=0; i<num; i++)
	{
		bestfit[i] = rocket[i].fit;
	}
	sort(bestfit, bestfit+num);
	
	for (int i=0; i<num; i++)
	{
		for (int j=0; j<5; j++)
		{
			if (rocket[i].fit == bestfit[num-1-j])
			{
				index[j] = i;
			}
		}
	}
	
	for (int i=0; i<5; i++)
	{
		copy(selected[i], rocket[index[i]]);
	}
	for (int i=0; i<5; i++)
	{
	//	cout<<index[i]<<"\n";
	}
}

void breed()
{
	
	int k=0;
	for (int i=0; i<4; i++)
	{
		for (int j=i+1; j<5; j++)
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
		if (rand()%mut1==0)
		for (int j=0; j<len; j++)
		{
			if (rand()%mut2==0)
			rocket[i].dna[j]=float(rand()%628)/100;
		}
	}
}

void showtarget()
{
	s.draw_circle_hollow(target.x, target.y, 10, 0 , 255, 0);
}

int main()
{
	srand(40002);
	
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
				rocket[i].calc_fit();
				//if(i==5)
			//	{
				//	vect k={cos(rocket[i].dna[time]), sin(rocket[i].dna[time]) - g};
					//cout<<mod(rocket[i].a)<<" ";
				//	cout<<mod(k);
			//	}
				showtarget();
			}
			s.Draw();
			Sleep(10);
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
