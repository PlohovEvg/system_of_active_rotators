#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <random>
#include <vector>
#include <omp.h>

using namespace std;

double* Set_Gamma(int _n, double gam1, double gam2);
int __clrcall compare(const void * val1, const void * val2);
int GetNumberOfClusters(const double *_Omega, const int _n);
double RK4(double t, double ts, double vn, double h, double d, double g, double E0, double E0_star, double alpha);
double f(double t, double _ts, double fi, double d, double _g, double _E0, double _E0_star, double _alpha);
double E(double t, double ts, double E0, double E0_star, double alpha);
double dEdt(double t, double ts, double E0, double E0_star, double alpha);
void FindMinMax(int arrcap, double *arr, double *minelem, double *maxelem);
void FindMinMax(int arrcap, int *arr, int *minelem, int *maxelem);