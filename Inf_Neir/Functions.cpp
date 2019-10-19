#include <cmath>
#include "Functions.h"

double RK4(double vn, double h, Ur d)
{
	double vn1, k1, k2, k3, k4;

	k1 = f(vn, d);
	k2 = f(vn + (h / 4.0)*k1, d);
	k3 = f(vn + (h / 2.0)*k2, d);
	k4 = f(vn + (h / 2.0)*(k1 - 2 * k2 + 2 * k3), d);
	vn1 = vn + (h / 6.0)*(k1 + 4 * k3 + k4);

	return vn1;
}

double xInc(double x, double h)
{
	return x + h;
}

double f(double u, Ur d)
{
	return d.gamma-sin(u);
}