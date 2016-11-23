#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "onedimlib.h"

int main(int argc, char* argv[]){
    if(argc < 6){
        printf("Provide outfile, numerical algorithm, dt, dx and dn as command line arguments!");
        return 1;
    }
    char *outfile = argv[1];
    char *method = argv[2];
    double h = atof(argv[3]);
    double dx = atof(argv[4]);
    int dn = atoi(argv[5]);
    double L = 1, end_t = 1;
    OneDimSolver *solver = new OneDimSolver(outfile,h,end_t,dx,L);
    if(strcmp(method,"forward_Euler") == 0){
        solver->forward_Euler(dn);
    }
    else if(strcmp(method,"backward_Euler") == 0){
        solver->backward_Euler(dn);
    }
    else{
        printf("Invalid method!");
        return 1;
    }
    delete solver;
}
