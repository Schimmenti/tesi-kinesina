#pragma once
#include "stdafx.h"

double exp_cdf_inv(double u, double tau)
{
	return -log(1 - u)*tau;
}
double uniform_sample(int seed)
{
	srand(seed);
	return (double)rand() / RAND_MAX;
}
double uniform_sample()
{
	return uniform_sample(time(NULL));
}

double* create_discr_cdf(double* p_i, int n)
{
	double* cdf = new double[n];
	cdf[0] = p_i[0];
	for (int i = 1; i < n; i++)
	{
		cdf[i] = cdf[i - 1] + p_i[i];
	}
	return cdf;
}
int sample_discr_cdf(double* cdf, int n, double u)
{
	for (int i = 0; i < n; i++)
	{
		if (u <= cdf[i])
		{
			return i;
		}
	}
}
