#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char *argv[]){
    if(argc < 5){
        printf("Provide filename (without extension), dt, dx and dn as command-line arguments!\n");
        return 1;
    }
    char *filename = argv[1];
    double dt = atof(argv[2]);
    double dx = atof(argv[3]);
    double dy = dx, pi = M_PI;
    int dn = atoi(argv[4]);

    int number_of_spatial = (int) round(1/dx);
    int number_of_timesteps = (int) round(1/dt);

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
            }
            else {
                x = i*dx;
                y = j*dy;
                u[i][j] = sin(pi*x)*sin(pi*y);
            }
        }
    }

    for(int i = 0; i < number_of_spatial; i++){
        delete [] u[i];
        delete [] u_new[i];
    }
    delete [] u;
    delete [] u_new;
}
