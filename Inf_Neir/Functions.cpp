#include <cmath>
#include "Functions.h"

double RK4(double x, double vn, double h, Ur d, double g, double En, double tn, double Qn, double alpha)
{
	double vn1, k1, k2, k3, k4;

	k1 = f(x, vn, d, g, En, tn, Qn, alpha);
	k2 = f(x + (h / 4.0), vn + (h / 4.0)*k1, d, g, En, tn, Qn, alpha);
	k3 = f(x + (h / 2.0), vn + (h / 2.0)*k2, d, g, En, tn, Qn, alpha);
	k4 = f(x + h, vn + (h / 2.0)*(k1 - 2 * k2 + 2 * k3), d, g, En, tn, Qn, alpha);
	vn1 = vn + (h / 6.0)*(k1 + 4 * k3 + k4);

	return vn1;
}

double xInc(double x, double h)
{
	return x + h;
}

double f(double x, double u, Ur d, double _g, double _En, double _tn, double _Qn, double _alpha)
{
	return d.gamma-sin(u)+_g*(_En+(x-_tn)*_Qn)*exp(-_alpha*(x-_tn));
}