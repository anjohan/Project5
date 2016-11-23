#include "onedimlib.h"

OneDimSolver::OneDimSolver(char *filename, double h_in, double end_t_in, double dx, double L_in){
    // Store stuff
    file = fopen(filename,"w");
    end_t = end_t_in;
    h = h_in;
    L = L_in;
    alpha = h/(dx*dx);

    //Initialise values
    n_t =  (int) round(end_t/h);
    n_x = (int) round(L/dx);
    x = new double[n_x+1];
    t = new double[n_t];
    u = new double[n_x+1];
    u[0] = 0; u[n_x-1] = 1;
    u_new = new double[n_x+1];
    u_new[0] = 0; u_new[n_x] = 1;

    //Initialise arrays for x and t, set end points explicitly
    int i;
    for(i=0; i<n_x-1; i++){
        x[i] = i*dx;
    }
    x[n_x] = L;

    //Write first line of output file
    fprintf(file,"$x$");
    for(i=0;i<=n_x; i++){
        fprintf(file," %g",x[i]);
    }
    fprintf(file,"\n");
}

void OneDimSolver::output(int i){
    fprintf(file,R"($t=\\num{%g}$)",h*i);
    for(int j = 0; j < n_x; j++){
        fprintf(file," %g",u[j]);
    }
    fprintf(file,"\n");
}

void OneDimSolver::forward_Euler(int output_dn){
    double prefactor = 1 - 2*alpha;
    double *tmp;
    output(0);
    for(int i = 0; i<n_t; i++){
        //Calculate new values in parallel
        #pragma omp parallel for
        for(int j = 1; j<n_x-1; j++){
            u_new[j] = prefactor * u[j] + alpha*(u[j+1] + u[j-1]);
        }
        //Swap new and old
        tmp = u_new;
        u_new = u;
        u = tmp;
        //Print if requested
        if(i % output_dn == 0){
            output(i+1);
        }
    }
    //Print final result
    output(n_t);
}

void OneDimSolver::backward_Euler(int output_dn){
    double prefactor = 1 + 2*alpha;
    double *tmp;
    double *a = new double[n_x];
    double *b = new double[n_x];
    double *c = new double[n_x];
    for(int i = 0; i<n_x; i++){
        a[i] = -alpha;
        b[i] = prefactor;
        c[i] = -alpha;
    }
    output(0);
    for(int i = 0; i<n_t; i++){
        u[n_x-2] += alpha;
        tridiagonalsolver(a,b,c,u,u_new,n_x-1);
        //Swap new and old
        tmp = u_new;
        u_new = u;
        u = tmp;
        //Print if requested
        if(i % output_dn == 0){
            output(i+1);
        }
    }
    //Print final result
    output(n_t);
    delete [] a;
    delete [] b;
    delete [] c;
}

void OneDimSolver::Crank_Nicolson(int output_dn){
    double beta = 2 + 2*alpha;
    double *tmp;
    double *a = new double[n_x];
    double *b = new double[n_x];
    double *c = new double[n_x];
    double *rhs = new double[n_x];
    for(int i = 0; i<n_x; i++){
        a[i] = -alpha;
        b[i] = beta;
        c[i] = -alpha;
    }
    output(0);
    for(int i = 0; i<n_t; i++){
        #pragma omp parallel for
        for(int j = 1; j < n_x-1; j++){
            rhs[j] = -alpha*(u[j-1]+u[j+1]) + beta*u[j];
        }
        u[n_x-2] += alpha;
        tridiagonalsolver(a,b,c,rhs,u_new,n_x-1);
        //Swap new and old
        tmp = u_new;
        u_new = u;
        u = tmp;
        //Print if requested
        if(i % output_dn == 0){
            output(i+1);
        }
    }
    //Print final result
    output(n_t);
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] rhs;
}
