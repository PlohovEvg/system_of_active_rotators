#pragma once
#include "Ur.h"
#define _USE_MATH_DEFINES
#include <math.h>
double RK4(double t, double ts, double vn, double h, Ur d, double g, double E0, double E0_star, double alpha);
double xInc(double x, double h);
double f(double t, double _ts, double fi, Ur d, double _g, double _E0, double _E0_star, double _alpha);
double E(double t, double ts, double E0, double E0_star, double alpha);
double dEdt(double t, double ts, double E0, double E0_star, double alpha);