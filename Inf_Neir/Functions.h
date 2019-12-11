#pragma once
#include "Ur.h"
#define _USE_MATH_DEFINES
#include <math.h>
double RK4(double x, double vn, double h, Ur d, double g, double tn, double alpha, double beta);
double xInc(double x, double h);
double f(double x, double u, Ur d, double _g, double _tn, double _alpha, double _beta);
double E(double x, double tn, double alpha, double beta);
double Q(double x, double tn, double alpha, double beta);