#include "onedimlib.h"

int main(){
    OneDimSolver *solver = new OneDimSolver("test.dat", 0.00001, 1, 0.01, 1);
    solver->forward_Euler(10);
    delete solver;
}
