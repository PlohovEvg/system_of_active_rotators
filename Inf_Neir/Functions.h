#pragma once
#include "Ur.h"
#define _USE_MATH_DEFINES
#include <math.h>
double RK4(double t, double vn, double h, Ur d, double g, double E0, double E0_star, double alpha, int N, int k);
double xInc(double x, double h);
double f(double t, double fi, Ur d, double _g, double _E0, double _E0_star, double _alpha, int _N, int _k);
double E(double t, double E0, double E0_star, double alpha, int N, int k);