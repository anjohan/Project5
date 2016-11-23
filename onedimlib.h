#ifndef onedim_h
#define onedim_h

#include <cstdio>
#include <cmath>
#include "tridiagonalsolver.h"

class OneDimSolver{
    public:
        OneDimSolver(char *filename, double h_in, double end_t_in, double dx, double L_in);
        ~OneDimSolver(){
            fclose(file);
            delete [] x;
            delete [] t;
            delete [] u;
            delete [] u_new;
        }
        void output(int i);
        void forward_Euler(int output_dn);
        void backward_Euler(int output_dn);
        void Crank_Nicolson(int output_dn);
    private:
        FILE *file;
        double end_t, L, alpha, h;
        double *x, *t, *u, *u_new;
        int n_t, n_x;
};


#endif
