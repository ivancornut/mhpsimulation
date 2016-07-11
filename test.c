#include <stdio.h>
#include <stdlib.h>
double * createlandscape(int x_size, int timeofsim);
int mod (int a, int b);
int main(int argc, char const *argv[])
{
	int i = mod(-1, 8);
	printf("%d\n",i );
	double *ptom = createlandscape(45, 20);
	void free(void * ptom);
	return 0;

}
int mod (int a, int b)
{
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}
double * createlandscape(int x_size, int timeofsim)
{
	// this creates the pointer to the array landscape, calloc allocates the size of array on the memory for the whole programm until it is freed
	double *landscape = calloc(timeofsim*x_size,sizeof(double));
	// this sets all the values in the array to zero
	double b = 0.1;
	int i = 0;
	while (i < timeofsim*x_size)
	{
		landscape[i] = b;
		printf("Hi\n");
		i++;
	}
	printf("This has worked eement %f \n", landscape[20]);
	// this returns the pointer to the array 
	return landscape;
}