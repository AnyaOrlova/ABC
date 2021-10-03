#ifndef FOO
#define FOO

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void benchmark(int num_test, int n, int matrix_size, double &avg_time,
               double &dispersion, double &abs_error, double &rel_error);
void get_cpu_name(char cpuname[]);

#endif
