//
// Created by mac on 2019/12/12.
//

#include "function.h"
#include <iostream>
#include <ctime>
#include <sys/resource.h>
#include <sys/time.h>

int evaluation_count = 0;

double F(double x)
{
    int i;
    for (i = 0; i < 500000; i++);

    evaluation_count++;
    return 4.0 / (1.0 + x * x);
}

double RESULT = 3.141592653589793;

void gettime(double *cpu, double *wall)
{
    struct timeval tv;
    struct rusage ru;

    if (cpu != NULL){
        getrusage(RUSAGE_SELF, &ru);
        *cpu = ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec * 1e-6;
    }
    if (wall != NULL) {
        gettimeofday(&tv, NULL);
        *wall = tv.tv_sec + (double) tv.tv_usec * 1e-6;
    }
}