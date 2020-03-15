#include "Functions.h"

double RK4(double t, double ts, double vn, double h, Ur d, double g, double E0, double E0_star, double alpha)
{
	double vnplus1, k1, k2, k3, k4;

	k1 = f(t, ts, vn, d, g, E0, E0_star, alpha);
	k2 = f(t + (h / 4.0), ts, vn + (h / 4.0)*k1, d, g, E0, E0_star, alpha);
	k3 = f(t + (h / 2.0), ts, vn + (h / 2.0)*k2, d, g, E0, E0_star, alpha);
	k4 = f(t + h, ts, vn + (h / 2.0)*(k1 - 2 * k2 + 2 * k3), d, g, E0, E0_star, alpha);
	vnplus1 = vn + (h / 6.0)*(k1 + 4 * k3 + k4);

	return vnplus1;
}

double xInc(double x, double h)
{
	return x + h;
}

double f(double t, double _ts, double fi, Ur d, double _g, double _E0, double _E0_star, double _alpha)
{
	double Et = E(t, _ts, _E0, _E0_star, _alpha);
	return d.gamma - sin(fi) + _g*Et;
}

double E(double t, double ts, double E0, double E0_star, double alpha)
{
	return exp(-alpha*(t - ts))*(E0 + (t - ts)*(E0_star + alpha*E0));
}

double dEdt(double t, double ts, double E0, double E0_star, double alpha)
{
	return exp(-alpha*(t - ts))*(-(alpha*alpha)*(t - ts)*E0 + E0_star*(1 - alpha*(t - ts)));
}
