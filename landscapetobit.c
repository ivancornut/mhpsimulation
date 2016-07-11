#include <stdio.h>
#include <string.h>
#include "qdbmp.h"
#include "landscapetobit.h"
int createfrommatrix(int x_size, int y_size, int red, int green, int blue,double *ptom,char name[])
{
	double *landscape = ptom;
	double moni = 0;
	int i = 0;
	int j = 0;
	// creating a bmp object and it's space in memory
	BMP* bmp = BMP_Create( x_size, y_size, 24 );
	// loop that runs throughout the whole array fed into this function
	while(j < x_size*y_size)
	{
		if(landscape[j] > moni)
		{
			moni = landscape[j];
			j++;
		}
		else
		{
			j++;
		}
	}

	while(i < x_size*y_size)
	{
		BMP_SetPixelRGB(bmp, i%x_size, i/x_size , 0 , 0 , landscape[i]/moni*255);
		i++;
	}
	
	// creates the file at the indicated name location 
	BMP_WriteFile( bmp, name );
	// frees the memory used by the bmp 
	BMP_Free(bmp);
	return 0 ;

}
int createfrommatrix2(int x_size, int y_size, int red, int green, int blue,double *ptom,char name[])
{
	double *landscape = ptom;
	double moni = 0;
	int i = 0;
	int j = 0;
	// creating a bmp object and it's space in memory
	BMP* bmp = BMP_Create( x_size, y_size, 24 );
	// loop that runs throughout the whole array fed into this function
	while(i < x_size*y_size)
	{
		BMP_SetPixelRGB(bmp, i%x_size, i/x_size , 0 , 0 , landscape[i]*255);
		i++;
	}
	
	// creates the file at the indicated name location 
	BMP_WriteFile( bmp, name );
	// frees the memory used by the bmp 
	BMP_Free(bmp);
	return 0 ;

}