#pragma once
#include "Ur.h"
double RK4(double x, double vn, double h, Ur d, double g, double En, double tn, double Qn, double alpha);
double xInc(double x, double h);
double f(double x, double u, Ur d, double _g, double _En, double _tn, double _Qn, double _alpha);