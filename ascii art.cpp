#include<iostream>
#include<render.h>
#include<fstream>

#define N 10

using namespace std;

Screen s(1000, 600);

char light[N] = {	' ',		//1
					char(39),		//2
					char(248),		//3
					char(251),		//4 
					char(246),		//5
					char(176),		//6
					char(177),		//7
					char(171),		//8
					char(178),		//9
					char(219)		//10
				};

int allot(int val)
{
	return (val*N)/256;
}

void readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    for (int j=height-1; j>=0; j--)
	{
		for (int i=0; i<width; i++)
		{
			//s.put_pixel(i, j, data[j * 3*width + i*3], data[j * 3*width + i*3 + 1], data[j * 3*width + i*3 + 2]);
			cout<<light[allot(data[j * 3*width + i*3])];
		}
		cout<<endl;
	}
	delete [] data;  // Free memory allocated for the a array.
	data = NULL;     // Be sure the deallocated memory isn't used.
}


int main()
{
//	unsigned char* data = new unsigned char[480000];
//	char filename[20];
	readBMP("flower2.bmp");
//	cin>>filename;
//	readBMP(filename);
//	s.Draw();
	return 0;
}
