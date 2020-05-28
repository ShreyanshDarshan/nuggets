// 3D Graph.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <render.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <conio.h>

#define dbl long double

using namespace std;


class Vector3D
{
public :
	dbl X;
	dbl Y;
	dbl Z;
	Vector3D operator / (dbl a)
	{
		return Vector3D(X / a, Y / a, Z / a);
	}
	Vector3D operator * (dbl a)
	{
		return Vector3D(X * a, Y * a, Z * a);
	}
	Vector3D operator + (Vector3D a)
	{
		return Vector3D(X + a.X, Y + a.Y, Z + a.Z);
	}
	Vector3D operator - (Vector3D a)
	{
		return Vector3D(X - a.X, Y - a.Y, Z - a.Z);
	}

	dbl Magnitude()
	{
		return sqrt(X*X + Y*Y + Z*Z);
	}
	Vector3D Unit()
	{
		return Vector3D(X, Y, Z) / Magnitude();
	}
	dbl dotProduct(Vector3D a)
	{
		return X*a.X + Y*a.Y + Z*a.Z;
	}
	Vector3D crossProduct(Vector3D a)
	{
		return Vector3D(Y*a.Z - Z*a.Y, Z*a.X - X*a.Z, X*a.Y - Y*a.X);
	}
	Vector3D()
	{
		X = Y = Z = 0;
	}
	Vector3D(dbl x, dbl y, dbl z)
	{
		X = x, Y = y, Z = z;
	}
};

class Camera
{
private:
	Vector3D focusPoint;

public:
	Vector3D Normal;
	Vector3D xAxis;
	Vector3D yAxis;
	Vector3D Location;
	dbl focalLength;


	void CalculateFocusPoint()
	{
		focusPoint = Location + Normal* focalLength;
	}
	Vector3D WorldToScreen(Vector3D Point)
	{
		CalculateFocusPoint();
		Vector3D dir = Point - focusPoint;
		Vector3D rel = Point - Location;
		if (focusPoint.dotProduct(Normal) * Point.dotProduct(Normal) < 0 || !dir.dotProduct(Normal) || focalLength > abs(rel.dotProduct(Normal)))
		{
			return Vector3D(-10000, -10000, -10000);
		}
		//cout << abs((Point - Location).dotProduct(Normal));

		dbl ln = Location.dotProduct(Normal);
		dbl lambda = (ln - Point.dotProduct(Normal)) / dir.dotProduct(Normal);
		Vector3D POI = Point + dir*lambda;
		rel = POI - Location;
		//find distance from x and y axis vectors
		double x = xAxis.dotProduct(rel);
		double y = yAxis.dotProduct(rel);
		//x *= 100;
		//y *= 100;
		return Vector3D(x, y, 0);
	}

	void rotateAxis(dbl theta)
	{
		yAxis = (yAxis* (cos(theta) / yAxis.Magnitude()) + yAxis.crossProduct(Normal) * (sin(theta) / yAxis.crossProduct(Normal).Magnitude()))  *yAxis.Magnitude();
		xAxis =(xAxis* (cos(theta) / xAxis.Magnitude()) + xAxis.crossProduct(Normal) * (sin(theta) / xAxis.crossProduct(Normal).Magnitude())) * xAxis.Magnitude();
	}

	Camera(Vector3D startLocation, dbl FocalLength)
	{
		Location = startLocation;
		Normal = (Vector3D(0,0,0)-startLocation).Unit();
		focalLength = FocalLength;
		//Create a random y Axis
		yAxis = Normal.crossProduct(Vector3D(10, 11, 41)).Unit();
		xAxis = Normal.crossProduct(yAxis).Unit();
	}
};

dbl function(dbl y, dbl x)
{
	//if(y < 50 && x < 50)
	return cos(sqrt(y*y+(x-5)*(x-5))*2);
	//return 0;
}

int main()
{
	Camera ca(Vector3D(10, 10, 10), 290);
	ca.Location = Vector3D(300.4, 0, 4);
	ca.yAxis = Vector3D(0, 0, 1);
	ca.xAxis = Vector3D(0, 1, 0);
	ca.Normal = ca.yAxis.crossProduct(ca.xAxis);//Vector3D(-1, 0, 0);
	Screen s(1000, 1000);
	while (true)
	{
		//if (_kbhit())
		//{
			char c;
			c=_getch();

			s.clear();
			switch (c)
			{
			case 'w':
				ca.Location = ca.Location +  ca.Normal;//*0.01;
				break;
			case 's':
				ca.Location = ca.Location - ca.Normal;//*0.01;
				break;
			case 'a':
				ca.Location = ca.Location - ca.xAxis;// * 0.01;		
				break;
			case 'd':
				ca.Location = ca.Location + ca.xAxis;// * 0.01;
				break;
			case 'g':
				ca.Location = ca.Location + ca.yAxis;// * 0.01;
				break;
			case 'h':
				ca.Location = ca.Location - ca.yAxis;// * 0.01;
				break;
			case 'q':
				ca.rotateAxis(0.1);
				break;
			case 'e':
				ca.rotateAxis(-0.1);
				break;
			}
		//}

		for (double x = -10; x <= 10; x+=0.05)
		{
			for (double y = -10; y <= 10; y+=0.05)
			{
				dbl z = function(y, x);
				//cout << z << "\n";
				Vector3D o = ca.WorldToScreen(Vector3D(x, y, z));
				//cout << o.X << " " << o.Y << " " << o.Z<< "\n";
				if (x>-10 && x<10 && y<10 && y>-10)
				s.put_pixel_2(o.X+ 500, o.Y + 800, 26, 26, 26);
				else
				s.put_pixel_2(o.X+ 500, o.Y + 800);
			}
		}
		s.Draw();
		cout << "render";
		//_getch();
		//s.clear();
	}
	_getch();
    return 0;
}
