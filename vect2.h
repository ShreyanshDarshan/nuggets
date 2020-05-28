#include<cmath>

struct vect2
{
	float x, y;

	vect2 operator + (vect2 const &v)
	{
		vect2 ans;
		ans.x = x + v.x;
		ans.y = y + v.y;
		return ans;
	}
	
	vect2 operator - (vect2 const &v)
	{
		vect2 ans;
		ans.x = x - v.x;
		ans.y = y - v.y;
		return ans;	
	}

	vect2 operator * (float const &k)
	{
		vect2 ans;
		ans.x = x*k;
		ans.y = y*k;
		return ans;	
	}
};

float mod(vect2 v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

float dist(vect2 r1, vect2 r2)
{
	return mod(r1-r2);
}
