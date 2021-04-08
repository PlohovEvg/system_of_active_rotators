#include "Calculating_functions.h"
#define PRECISION 5e-04

double* Set_Gamma(const int _n, const double gam0, const double delt)
{
	double *g = new double[_n];
	random_device gen;
	mt19937 me(gen());
	uniform_real_distribution<> distr(-0.5, 0.5);

	for (int i = 0; i < _n; i++)
	{
		g[i] = gam0 + delt*distr(me);

	}
	return g;
}

double* Set_Gamma_in_range(const int _n, const double gam1, const double gam2)
{
	double *g = new double[_n];
	random_device gen;
	mt19937 me(gen());
	uniform_real_distribution<> distr(gam1, gam2);

	for (int i = 0; i < _n; i++)
	{
		g[i] = distr(me);

	}
	return g;
}

int __clrcall compare(const void * val1, const void * val2)
{
	const double *a, *b;
	a = (const double*)val1;
	b = (const double*)val2;

	if (*a > *b)
	{
		return 1;
	}
	else
	{
		if (*a < *b)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

int GetNumberOfClusters(const double *_Omega, const int _n)
{
	int ClusterNum = 0;
	int *Classes = new int[_n];
	double cur;
	bool flag;
	bool only_one_element_in_cluster;

	for (int i = 0; i < _n; i++)
	{
		Classes[i] = 0;
	}

	for (int i = 0; i < _n; i++)
	{
		if (Classes[i] == 0)
		{
			flag = false;
			cur = _Omega[i];
			only_one_element_in_cluster = true;

			for (int j = i + 1; j < _n; j++)
			{
				if (((abs(cur - _Omega[j]) < PRECISION) || (cur == _Omega[j])) && (Classes[j] == 0))
				{
					Classes[i] = Classes[j] = ClusterNum + 1;
					flag = true;
					only_one_element_in_cluster = false;
				}
			}

			if (only_one_element_in_cluster == true)
			{
				Classes[i] = ClusterNum + 1;
			}

			if ((flag == true) || (only_one_element_in_cluster))
			{
				ClusterNum++;
			}
		}
	}


	delete[]Classes;
	return ClusterNum;
}

double RK4(double t, double ts, double vn, double h, double d, double g, double E0, double E0_star, double alpha)
{
	double vnplus1, k1, k2, k3, k4;

	k1 = f(t, ts, vn, d, g, E0, E0_star, alpha);
	k2 = f(t + (h*0.5), ts, vn + (h*0.5)*k1, d, g, E0, E0_star, alpha);
	k3 = f(t + (h*0.5), ts, vn + (h*0.5)*k2, d, g, E0, E0_star, alpha);
	k4 = f(t + h, ts, vn + h*k3, d, g, E0, E0_star, alpha);
	vnplus1 = vn + (h / 6.0)*(k1 + 2 * k2 + 2 * k3 + k4);

	return vnplus1;
}

double f(double t, double _ts, double fi, double d, double _g, double _E0, double _E0_star, double _alpha)
{
	double Et = E(t, _ts, _E0, _E0_star, _alpha);
	return d - sin(fi) + _g*Et;
}

double E(double t, double ts, double E0, double E0_star, double alpha)
{
	return exp(-alpha*(t - ts))*(E0 + (t - ts)*(E0_star + alpha*E0));
}

double dEdt(double t, double ts, double E0, double E0_star, double alpha)
{
	return exp(-alpha*(t - ts))*(-(alpha*alpha)*(t - ts)*E0 + E0_star*(1 - alpha*(t - ts)));
}

void FindMinMax(int arrcap, double *arr, double *minelem, double *maxelem)
{
	*minelem = *maxelem = arr[0];

	for (int i = 1; i < arrcap; i++)
	{
		if (arr[i] > *maxelem)
		{
			*maxelem = arr[i];
		}
		if (arr[i] < *minelem)
		{
			*minelem = arr[i];
		}
	}
}

void FindMinMax(int arrcap, int *arr, int *minelem, int *maxelem)
{
	*minelem = *maxelem = arr[0];

	for (int i = 1; i < arrcap; i++)
	{
		if (arr[i] > *maxelem)
		{
			*maxelem = arr[i];
		}
		if (arr[i] < *minelem)
		{
			*minelem = arr[i];
		}
	}
}
