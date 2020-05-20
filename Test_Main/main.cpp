#include <stdlib.h>
#include <ctime>
#include <iostream>

using namespace std;

int comp(const void * val1, const void * val2)
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

int main()
{
	int n = 10;
	double *a = new double[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = (double)rand() / RAND_MAX;
	}
	qsort(a, n, sizeof(double), comp);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}