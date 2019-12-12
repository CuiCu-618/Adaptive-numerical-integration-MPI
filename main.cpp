/**
 * @file main.cpp
 * @author Cui Cu
 *
 * @brief Adaptive numerical integration
 *
 * Parallel algorithm based on simple domain decomposition \n
 * \f$ f(x) \in [a,b], \f$ \n
 * Trapezoid rule:
 * \f[
 *      \int_{a}^{b} f(x) dx \approx (b-a)\frac{f(a)+f(b)}{2}
 * \f]
 *
 * Composite Trapezoid rule:
 * \f[
 *      \int_{a}^{b} f(x) dx \approx \frac{1}{2}\sum^n_{i=1}(x_i-x_{i-1})(f(x_{i-1})+f(x_i))
 * \f]
 */





#include <iostream>
#include "mpi.h"
#include "integration.h"
#include "function.h"
#include <cmath>
using namespace std;

void s();
void p();
int main()
{
//    s();
    p();
    return 0;
}

void s(){
    double a = 0.0, b = 1.0;
    double res, cpu0, cpu1, wall0, wall1;
    double eps = 1e-8;
    gettime(&cpu0, &wall0);
    res = integration(a, F(a), b, F(b), eps / (b - a), F);
    gettime(&cpu1, &wall1);
    cout << "s(): " << endl;
    cout << "result = " << res << endl
         << "error = " << fabs(res - RESULT) << endl
         << "cpu time = " << cpu1 - cpu0 << endl
         << "wall time = " << wall1 - wall0 << endl
         << "evaluation_count = " << evaluation_count << endl;
}

void p()
{
    int nprocs, myrank;
    double a = 0.0, b = 1.0;
    double a0, b0, res, res0, cpu_local, cpu, cpu0, cpu1, wall0, wall1, wall2;
    double eps;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0){
        cout << "p(): " << endl;
        eps = 1e-8;
    }
    MPI_Bcast(&eps, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    a0 = a + (myrank + 0) * (b - a) / nprocs;
    b0 = a + (myrank + 1) * (b - a) / nprocs;

    gettime(&cpu0, &wall0);
    res0 = integration(a0, F(a0), b0, F(b0), eps / (b - a), F);
    gettime(&cpu1, &wall1);
    cpu_local = cpu1 - cpu0;
    cout << "Rank = " << myrank << " of evaluations = "
         << evaluation_count << ", cpu time = " << cpu_local
         << ", wall time = " << wall1 - wall0 << endl;
    MPI_Reduce(&res0, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&cpu_local, &cpu, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    gettime(NULL, &wall2);

    int max_evaluation;
    int total;

    MPI_Reduce(&evaluation_count, &max_evaluation, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&evaluation_count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myrank == 0){
        cout << "result = " << res
             << ", error = " << fabs(res-RESULT)
             << ", wall time = " << wall2 - wall0
             << ", cpu time = " << cpu << endl
             << "speedup ratio = " << 1.0 * cpu / (wall2 - wall0)
             << ", Load balancing efficiency = " << 1.0 * total / (nprocs * max_evaluation) << endl;

    }



    MPI_Finalize();

}