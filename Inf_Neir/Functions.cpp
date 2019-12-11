#include "Functions.h"

double RK4(double x, double vn, double h, Ur d, double g, double tn, double alpha, double beta)
{
	double vn1, k1, k2, k3, k4;

	k1 = f(x, vn, d, g, tn, alpha, beta);
	k2 = f(x + (h / 4.0), vn + (h / 4.0)*k1, d, g, tn, alpha, beta);
	k3 = f(x + (h / 2.0), vn + (h / 2.0)*k2, d, g, tn, alpha, beta);
	k4 = f(x + h, vn + (h / 2.0)*(k1 - 2 * k2 + 2 * k3), d, g, tn, alpha, beta);
	vn1 = vn + (h / 6.0)*(k1 + 4 * k3 + k4);

	return vn1;
}

double xInc(double x, double h)
{
	return x + h;
}

double f(double x, double u, Ur d, double _g, double _tn, double _alpha, double _beta)
{
	double Et = E(x, _tn, _alpha, _beta);	
	return d.gamma - sin(u) + _g*Et;
}

double E(double x, double tn, double alpha, double beta)
{
	return exp(-alpha*(x - tn))*(E(n) + (x - tn)*Q(n));
}

double Q(double x, double tn, double alpha, double beta)
{
	if (x - tn)
	{
		return Q(n)*exp(-alpha*(x - tn)) + beta;
	}
	else
	{
		return Q(n)*exp(-alpha*(x - tn));
	}
	
}