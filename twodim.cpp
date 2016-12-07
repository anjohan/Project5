#include <cstdio>
#include <cstdlib>
#include <cmath>

void output(char *filename, double **u, int N, double t);

int main(int argc, char *argv[]){
    if(argc < 5){
        printf("Provide filename (without extension), dt, dx and dn as command-line arguments!\n");
        return 1;
    }
    char *infile = argv[1];
    char *filename = new char[100];
    double dt = atof(argv[2]);
    double dx = atof(argv[3]);
    double dy = dx, pi = M_PI;
    double alpha = dt/(dx*dx), factor = 1 - 4*alpha;
    int dn = atoi(argv[4]);

    int number_of_spatial = (int) round(1/dx) + 1;
    int number_of_timesteps = (int) round(1/dt) + 1;
    dn = dn > number_of_timesteps ? number_of_timesteps : dn;

    double **u = new double*[number_of_spatial];
    double **u_new = new double*[number_of_spatial];
    for(int i = 0; i < number_of_spatial; i++){
        u[i] = new double[number_of_spatial];
        u_new[i] = new double[number_of_spatial];
    }

    double x, y;
    for(int i = 0; i < number_of_spatial; i++){
        for(int j = 0; j < number_of_spatial; j++){
            if(i == 0 || i == number_of_spatial-1 || j == 0 || j == number_of_spatial-1){
                u[i][j] = 0;
                u_new[i][j] = 0;
            }
            else {
                x = i*dx;
                y = j*dy;
                u[i][j] = sin(pi*x)*sin(pi*y);
            }
        }
    }

    double **tmp, t;
    sprintf(filename,"%s%.8f.dat",infile,0.0);
    output(filename,u,number_of_spatial,0);
    for(int k = 1; k < number_of_timesteps+1; k++){
        #pragma omp parallel for collapse(2)
        for(int i = 1; i < number_of_spatial-1; i++){
            for(int j = 1; j < number_of_spatial-1; j++){
                u_new[i][j] = factor*u[i][j] + alpha*(u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]);
            }
        }
        tmp = u;
        u = u_new;
        u_new = tmp;
        if(k % dn == 0){
            t = k * dt;
            sprintf(filename,"%s%.8f.dat",infile,t);
            output(filename,u,number_of_spatial,t);
        }
    }


    for(int i = 0; i < number_of_spatial; i++){
        delete [] u[i];
        delete [] u_new[i];
    }
    delete [] u;
    delete [] u_new;
    delete [] filename;
}

void output(char *filename, double **u, int N, double t){
    FILE *file = fopen(filename,"w");
    fprintf(file,"# %g\n",t);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fprintf(file,"%g ",u[i][j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}
