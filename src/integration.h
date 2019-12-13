//
// Created by mac on 2019/12/12.
//


#ifndef MPI_INTEGRATION_H
#define MPI_INTEGRATION_H
/**
 * @brief Compute \f$ \int_{a}^{b} f(x) \f$
 * @param a Left endpoint
 * @param fa value at point a
 * @param b Right endpoint
 * @param fb value at point b
 * @param eps eps
 * @param F Function
 * @return integration
 */
double integration(double a, double fa, double b, double fb, double eps, double(*F)(double x));
#endif //MPI_INTEGRATION_H
