#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "onedimlib.h"

int main(int argc, char* argv[]){
    if(argc < 7){
        printf("Provide outfile, numerical algorithm, dt, end_t, dx and dn as command line arguments!");
        return 1;
    }
    char *outfile = argv[1];
    char *method = argv[2];
    double dt = atof(argv[3]);
    double end_t = atof(argv[4]);
    double dx = atof(argv[5]);
    int dn = atoi(argv[6]);
    double L = 1;
    OneDimSolver *solver = new OneDimSolver(outfile,dt,end_t,dx,L);
    if(strcmp(method,"forward_Euler") == 0){
        solver->forward_Euler(dn);
    }
    else if(strcmp(method,"backward_Euler") == 0){
        solver->backward_Euler(dn);
    }
    else if(strcmp(method,"Crank_Nicolson") == 0){
        solver->Crank_Nicolson(dn);
    }
    else{
        printf("Invalid method!");
        return 1;
    }
    delete solver;
}
