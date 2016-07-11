#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "land.h"
#include "mt64.h"
// defining constants
int main(int argc, char *argv[])
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	int x_size = 200;
	int timeofsim = 1000;
	double mu = 0.0025;
	double drate = 0.0009833;
	double K = 20000;
	double lambda = 0.000666666;
	double epsilon = 0.15;
	double diffs = 0.00000036;
	double diffp = 0.00000519;
	double xip = 0;//0.00000000171;
	double xis = 0;//0.0013;
	double dist = 0.005;
	double inis = 0.394;
	double inip = 2747;
	long long seed = time(NULL);
//	printf("Your landscape will have a size of %ld. \n",total_size);
	runsimulationbmp(x_size, timeofsim, mu, drate, K, lambda, epsilon, diffs, diffp, xip, xis, dist, inis, inip, seed);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
	return 0;

}	

