#include<iostream>
#include<conio.h>
#include<cmath>
#include<string.h>
#include<dos.h>
#include <Windows.h>
using namespace std;

void disp(char a[300][120])
{
  for(int k=119; k>=0; k--)
  {
    for (int l=0; l<300; l++)
    {
      switch (a[l][k])
      {  
        case '*': SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 3); break;
        case '@': SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 6); break;
        case '#': SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 5); break;
        default : SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7); break;
        //cout<<"."      
      }     
      cout<<a[l][k]<<' ';
    }
    cout<<endl;
  }

}

int main()
{
  float scale_x, scale_y;
  cout<<"Enter the scale on x axis";
  cin>>scale_x;
  cout<<"Enter the scale on y axis";
  cin>>scale_y;
  double lc_x,lc_y,x,y;
  lc_x=(1/scale_x);
  lc_y=(1/scale_y);
  //cout<<lc;
  char a[300][120];

  for (int i=0; i<300; i++)
  {
    for (int h=0; h<120; h++)
    {
      a[i][h]=' ';
      a[150][h]='|';
      if (h%5==0)
      a[150][h]='+';    
    }
    a[i][60]='-';
    if (i%5==0)
    a[i][60]='+'; 
  }
  a[150][60]='+';
  for (int i=0; i<300; i++)
  {
    x=lc_x*(i-150);
    //if (x<=6)
    
    y= sin(x);                   // this is the function

    double r=y/lc_y;
    int j;
    j=(int)r/1.3 + 60;
    if (j>=0 && j<120)
    {
      //a[i][j]='*';
    }
   // cout<<"i="<<i<<" and j="<<j<<" and y="<<y<<endl;
  //  getch();
  }
  
  for (int i=0; i<300; i++)
  {
    x=lc_x*(i-150);
    //if (x<=6)
    
//    y= cos(x)-x;                   // this is the function
   if (x>=-1 && x<=1)
    
    y= -sqrt(1-x*x);                   // this is the function

    double r=y/lc_y;
    int j;
    j=(int)r/1.3 + 60;
    if (j>=0 && j<120)
    {
      a[i][j]='@';
    }
   // cout<<"i="<<i<<" and j="<<j<<" and y="<<y<<endl;
  //  getch();
  }
  
  for (int i=0; i<300; i++)
  {
    x=lc_x*(i-150);
   if (x>=-1 && x<=1)
    
    y= sqrt(1-x*x);                   // this is the function

    double r=y/lc_y;
    int j;
    j=(int)r/1.3 + 60;
    if (j>=0 && j<120)
    {
      a[i][j]='#';
    }
   // cout<<"i="<<i<<" and j="<<j<<" and y="<<y<<endl;
  //  getch();
  }
  
  disp(a);
  getch();
  return 0;
}
