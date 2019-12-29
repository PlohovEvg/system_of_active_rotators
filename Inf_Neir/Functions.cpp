#include "Functions.h"

double RK4(double t, double vn, double h, Ur d, double g, double E0, double E0_star, double alpha, int N, int k)
{
	double vnplus1, k1, k2, k3, k4;

	k1 = f(t, vn, d, g, E0, E0_star, alpha, N, k);
	k2 = f(t + (h / 4.0), vn + (h / 4.0)*k1, d, g, E0, E0_star, alpha, N, k);
	k3 = f(t + (h / 2.0), vn + (h / 2.0)*k2, d, g, E0, E0_star, alpha, N, k);
	k4 = f(t + h, vn + (h / 2.0)*(k1 - 2 * k2 + 2 * k3), d, g, E0, E0_star, alpha, N, k);
	vnplus1 = vn + (h / 6.0)*(k1 + 4 * k3 + k4);

	return vnplus1;
}

double xInc(double x, double h)
{
	return x + h;
}

double f(double t, double fi, Ur d, double _g, double _E0, double _E0_star, double _alpha, int _N, int _k)
{
	double Et = E(t, _E0, _E0_star, _alpha, _N, _k);
	return d.gamma - sin(fi) + _g*Et;
}

double E(double t, double E0, double E0_star, double alpha, int N, int k)
{
	return E0*exp(-alpha*t) + ((E0_star + alpha*E0 - k*((alpha*alpha) / N)) / (1 - alpha))*t*exp(-alpha*t);
}

