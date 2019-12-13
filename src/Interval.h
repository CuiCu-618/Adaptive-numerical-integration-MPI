//
// Created by mac on 2019/12/13.
//

#ifndef MPI_INTERVAL_H
#define MPI_INTERVAL_H


class Interval {
public:
    Interval(double a, double b);
    double get_left();
    double get_right();

private:
    double a;
    double b;
};


#endif //MPI_INTERVAL_H
