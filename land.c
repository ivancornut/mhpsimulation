#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "mt64.h"
#include "land.h"
#include "landscapetobit.h"
void create_marks_csv(char *filename,double *ptom,int x_size,int timeofsim)
{
 	
 	double *landscape = ptom;
	printf("\n Creating %s.csv file",filename);
 	FILE *fp;
 	int i,j;
 	filename=strcat(filename,".csv");
 	fp=fopen(filename,"w+");
	for(i=0;i<timeofsim;i++)
	{
 		fprintf(fp,"\n");
		
		for(j=0;j<x_size;j++)
   		{
    	fprintf(fp,"%f,",landscape[j+i*x_size]);
    	}
    }
 	
 	fclose(fp);
	printf("\n %sfile created",filename);
 }

int mod(int a, int b)
{
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

double * createlandscape(int x_size, int timeofsim,double ini)
{
	// this creates the pointer to the array landscape, calloc allocates the size of array on the memory for the whole programm until it is freed
	double *landscape = calloc(timeofsim*x_size,sizeof(double));
	// this sets all the values in the array to zero
	int i = 0;
	while (i < x_size)
	{
		landscape[i] = ini;
		i++;
	}
	printf("This has worked element %f \n", landscape[20]);
	// this returns the pointer to the array 
	return landscape;
}
double * createlandscape2(int x_size, int timeofsim,double ini)
{
	// this creates the pointer to the array landscape, calloc allocates the size of array on the memory for the whole programm until it is freed
	double *landscape = calloc(timeofsim*x_size,sizeof(double));
	// this sets all the values in the array to zero
	//int i = 0;
	//while (i < x_size)
	//{
	//	landscape[i] = ini;
	//	i++;
	//}
	landscape[50] = 8000;
	landscape[49] = 8000;
	landscape[51] = 8000;
	printf("This has worked element %f \n", landscape[20]);
	// this returns the pointer to the array 
	return landscape;
}

double * update_substrate(int x_size, double *landscape, int t, double lambda, double epsilon, int K, double mu, double *slandscape )
{
//	double *landscape = ptom;
//	double *slandscape = ptoms;
	double subs = 0;
	int bact = 0;
	int i = 0;
	int line = t*x_size;
	while (i < x_size)
	{
		subs = slandscape[line+i];
		bact = landscape[line+i];
		slandscape[line+i+x_size] = subs + (lambda*(1-subs)-epsilon*mu*subs*bact/K);////(lambda*(1-subs)
		i++;
	}
	return slandscape;
}

double * lifeanddeath(int x_size, double *ptom, int t, double mu, double drate,double K, double *ptoms, long long seed)
{
//	init_genrand64(seed);
	double *landscape = ptom;
	double *slandscape = ptoms;
	double rmu = 0;
	double rd = 0;
	double probmu = 0;
	int i = 0;
	int j = 0;
	double bact = 0;
	double subs = 0;
	int line = t*x_size;
//	#pragma omp parallel for private(i,j,rmu,bact,probmu,subs,rd,drate,mu) shared(landscape,slandscape,line,x_size)
	for(i= 0; i < x_size; i++)
	{
		bact = landscape[line+i];
		subs =  slandscape[line+i];
		j = 0;
		probmu = mu*subs-(mu*subs-drate)*bact/K;
		for(j = 0; j < bact;j++)
		{
			rmu = genrand64_real1();
			rd  = genrand64_real1();
			if (rmu < probmu && rd > drate)
			{
				landscape[line+i] = landscape[line+i]+1;
			}
			else if(rmu > probmu && rd < drate)
			{
				landscape[line+i]  = landscape[line+i]-1;
			}
		}
	}
	return landscape;
}
double * bactmove(int x_size, int t, double *ptom, double *ptoms, double diffp, double xip, double xis, double dist, long long seed)
{
	double *landscape = ptom;
	double *slandscape = ptoms;
	double pStay = 0;
	double pLeft = 0;
	double pRight = 0;
	int leftn = 0;
	int rightn = 0;
	double q = 0;
	int bact = 0;
	init_genrand64(seed);
	int j = 0;
	int i = 0;
	int line = t*x_size;
	double distsq = dist*dist;
//#pragma omp parallel for private(i,j,leftn,rightn,bact,pStay,pRight,pLeft,q) shared(landscape,slandscape,line,x_size,distsq,diffp,xis,xip)
	for(j = 0;j < x_size; j++)
	{
		leftn = mod(j-1,x_size);
		rightn = mod(j+1,x_size);
//		printf("youhou\n");
		bact = landscape[line+j];
		pStay = 1-2*diffp/(distsq)-xis/(distsq)*(slandscape[line+rightn]-2*slandscape[line+j]+slandscape[line+leftn])-xip/(distsq)*(landscape[line+rightn]-2*landscape[line+j]+landscape[line+leftn]);
		pLeft = diffp/(distsq)-xis/(4*distsq)*(slandscape[line+rightn]-slandscape[line+leftn])-xip/(4*distsq)*(landscape[line+rightn]-landscape[line+leftn]);
		pRight = diffp/(distsq)-xis/(4*distsq)*(slandscape[line+leftn]-slandscape[line+rightn])-xip/(4*distsq)*(landscape[line+leftn]-landscape[line+rightn]);
//#pragma omp parallel for private(i,q) shared(landscape,line,x_size,pStay,pRight,pLeft,rightn,leftn,bact)
		for (i = 0;i < bact ; i++)
		{
			q = genrand64_real1()*(pStay+pLeft+pRight);
			if(q < pStay)
			{
				landscape[line+j+x_size] = landscape[line+j+x_size]+1;
			}
			else if(q > pStay && q < (pRight+pStay))
			{
				landscape[line+rightn+x_size] = landscape[line+rightn+x_size]+1;
//				landscape[line+j+x_size] = landscape[line+j]-1;
			}
			else if (q > pRight && q < (pLeft+pStay+pRight))
			{
				landscape[line+leftn+x_size] = landscape[line+leftn+x_size]+1;
//				landscape[line+j+x_size] = landscape[line+j]-1;
			}
		}
	}
	return landscape;
}
double * diffsub(int x_size, int t, double *ptoms, double diffs, double dist)
{
	double *slandscape = ptoms;
	int leftn = 0;
	int rightn = 0;
	int i = 0;
	double distsq = dist;
	double delta = 0;
	int line = x_size*(t+1);
	while(i < x_size)
	{
		leftn = mod(i-1,x_size);
		rightn = mod(i+1,x_size);
		delta = diffs*(slandscape[line+leftn]-2*slandscape[line+i]+slandscape[line+rightn])/distsq;
		slandscape[line+x_size+i] = slandscape[line+i]+delta;
		i++;
	}
	return slandscape;
}
int runsimulationbmp(int x_size, int timeofsim, double mu, double drate, double K, double lambda, double epsilon, double diffs, double diffp, double xip, double xis, double dist,double inis, double inip, long long seed)
{
	init_genrand64(seed);
	double *ptom = createlandscape2(x_size, timeofsim, inip);
	double *ptoms = createlandscape(x_size, timeofsim, inis);
	int t = 0;
	createfrommatrix( x_size, timeofsim, 0, 0, 0, ptom, "ini.bmp");
	createfrommatrix( x_size, timeofsim, 0, 0, 0, ptoms, "inis.bmp");
	while (t < (timeofsim-2))
	{
		ptoms = substrate(x_size, ptom, t, lambda, epsilon, K, mu, ptoms );
		ptoms = diffsub(x_size, t, ptoms, diffs, dist);
		ptom = lifeanddeath( x_size, ptom, t, mu, drate, K, ptoms, genrand64_int64());
		ptom = bactmove( x_size, t, ptom, ptoms, diffp, xip, xis, dist, genrand64_int64());
		if (t%20 == 1)
		{
			printf("%d\n",t);
			t++;
		}
		else
		{
			t++;
		}
	}
	createfrommatrix( x_size, timeofsim, 0, 255, 0, ptom, "bit.bmp");
	char str[100];
	printf("\n Enter the filename :");
	//str = "Youlu"
	scanf("%s",str);
	create_marks_csv(str, ptom, x_size, timeofsim);
	createfrommatrix2( x_size, timeofsim, 0, 0, 0, ptoms, "bits.bmp");
	printf("Your simulation ran for time %d is finished and bmp files were created\n",timeofsim );
	void free(void * ptom); 
	void free(void * ptoms); 
	return 0;
}
