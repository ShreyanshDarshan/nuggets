#include<iostream>
#include<conio.h>
#include<render.h>

#define N 100

using namespace std;

char entstr[N];
char polish[N];
char expr[N];
float calc[N];
int p=-1, c=-1, e=-1;

void push_p (char a)
{
	p++;
	polish[p]=a;
	polish[p+1]='\0';
}

void push_e (char a)
{
	e++;
	expr[e]=a;
	expr[e+1]='\0';
}

void push_c (float a)
{
	c++;
	calc[c]=a;
}

char pop_p ()
{
	if (p>=0)
	{
		char temp = polish[p];
		p--;
		return temp;
	}
	else
	cout<<"can't pop_p";
}

char pop_e ()
{
	if (e>=0)
	{
		char temp = expr[e];
		e--;
		return temp;
	}
	else
	cout<<"can't pop_e";
}

float pop_c ()
{
	if (c>=0)
	{
		float temp = polish[p];
		c--;
		return temp;
	}
	else
	cout<<"can't pop_c";
}

void fill_pol(char a)
{	char t=' ';
	switch(a)
	{
		case '(':	push_p(a);	break;
		case ')':	t=pop_p();
					while (t!='(')
					{
						push_e(t);
						t=pop_p();
					}
					break;
		
		case '^':	push_
		
		case '/':	t=pop_p();
					if (t=='^')
					{
						push_e(t);
						push_p(a);
					}
					else
					{
						push_p(t);
						push_p(a);	
					}		
					break;
		
		case '*':	t=pop_p();
					if (t=='^')
					{
						push_e(t);
						push_p(a);
					}
					else
					{
						push_p(t);
						push_p(a);	
					}		
					break;
				
		case '+':	t=pop_p();
					if (t=='-' || t=='*' || t=='/')
					{
						push_e(t);
						push_p(a);
					}
					else
					{
						push_p(t);
						push_p(a);	
					}		
					break;
		
		case '-':	t=pop_p();
					if (t=='*' || t=='/')
					{
						push_e(t);
						push_p(a);
					}
					else
					{
						push_p(t);
						push_p(a);	
					}		
					break;					
		default :	push_e(a);
	}
}

int main()
{
	cin.getline(entstr+1, N);
	entstr[0]='(';
	entstr[strlen(entstr)]=')';
	cout<<entstr;
	getch();
	for (int i=0; i<strlen(entstr); i++)
	{
		fill_pol(entstr[i]);
		cout<<polish<<"\n";
		cout<<expr;
		getch();
		system("cls");
	}
	
	return 0;
}
