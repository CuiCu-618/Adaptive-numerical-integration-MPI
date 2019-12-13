//
// Created by mac on 2019/12/13.
//

#ifndef MPI_INTEGRATION_NE_H
#define MPI_INTEGRATION_NE_H

#include <cmath>
#include <queue>
#include <iostream>
#include "function.h"
#include "Interval.h"

using namespace std;

double integration_ne(double a, double b, int &max)
{

    double res = 0.0;
    double x0, x1, xc, h, v0, v1;
    int count = 0;
    max = 0;
    const double ESP = 3 * 4e-4;
    Interval I(a, b);
    if (a == b)
        cout << res << endl;
    queue<Interval> C;
    C.push(I);
    while (!C.empty()){
        unsigned int sz = C.size();
        for (unsigned int i = 0; i < sz; i++){
            x0 = C.front().get_left();
            x1 = C.front().get_right();
            xc = (x0 + x1) / 2.0;
            h = x1 - x0;
            v0 = h * (F(x0) + F(x1)) / 2.0;
            v1 = (v0 + F(xc) * h) / 2.0;
            if (fabs(v0 - v1) < h * ESP){
                res += v1;
                C.pop();
                count--;
            } else {
                C.pop();
                Interval I1(x0, xc);
                Interval I2(xc, x1);
                count++;
                C.push(I1);
                C.push(I2);
                if (count > max)
                    max = count;
            }
        }
    }

    return res;
}

#endif //MPI_INTEGRATION_NE_H
