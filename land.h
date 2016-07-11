void create_marks_csv(char *filename,double *ptom,int x_size,int timeofsim);

int mod(int a, int b);

double * createlandscape(int x_size, int timeofsim,double ini);

double * createlandscape2(int x_size, int timeofsim,double ini);

double * substrate(int x_size, double *ptom, int t, double lambda, double epsilon, int K, double mu, double *ptoms);

double * lifeanddeath(int x_size, double *ptom, int t, double mu, double drate,double K, double *ptoms, long long seed);

double * bactmove(int x_size, int t, double *ptom, double *ptoms, double diffp, double xip, double xis, double dist, long long seed);

double * diffsub(int x_size, int t, double *ptoms, double diffs, double dist);

int runsimulationbmp(int x_size, int timeofsim, double mu, double drate, double K, double lambda, double epsilon, double diffs, double diffp, double xip, double xis, double dist,double inis, double inip, long long seed);