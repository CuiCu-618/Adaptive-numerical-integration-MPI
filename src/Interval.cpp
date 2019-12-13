//
// Created by mac on 2019/12/13.
//

#include "Interval.h"
Interval::Interval(double a, double b) {
    this->a = a;
    this->b = b;
}
double Interval::get_left() {
    return a;
}
double Interval::get_right() {
    return b;
}