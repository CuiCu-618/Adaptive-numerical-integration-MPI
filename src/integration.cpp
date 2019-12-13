//
// Created by mac on 2019/12/12.
//

#include "integration.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

#define MAX_DEPTH 1024
#define MACHINE_PREC 1e-15

double integration(double a, double fa, double b, double fb, double eps, double(*F)(double x))
{
    static int depth = 0;
    double fc, v0, v, h, xc;

    ++depth;
    v = 0.0;
    if(a != b){
        xc = (a + b) * 0.5;
        h = b - a;
        v0 = h * (fa + fb) * 0.5;
        if(xc != a && xc != b){
            double err;
            fc = (*F)(xc);
            v = (v0 + fc * h) * 0.5;
            err = fabs(v - v0);
            if ((err >= 3.0 * h * eps) && (fabs(h) >= (1.0 + fabs(xc)) * MACHINE_PREC)){
                v = integration(a, fa, xc, fc, eps, F) + integration(xc, fc, b, fb, eps, F);
            }
        }
    }
    --depth;
    return v;
}
