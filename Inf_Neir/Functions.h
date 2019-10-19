#pragma once
#include "Ur.h"
double RK4(double vn, double h, Ur d);
double xInc(double x, double h);
double f(double u, Ur d);