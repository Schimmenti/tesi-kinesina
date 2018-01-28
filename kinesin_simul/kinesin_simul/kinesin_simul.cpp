// kinesin_simul.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include "master_eq_ssa.h"
#include "kinesin.h"
#include <iostream>
using namespace std;
int main()
{
	int epochs = 1000;
	double* v_i = new double[epochs];
	double* r_i = new double[epochs];

	double f = -4;
	double dmu = normalize_chem(3.5);
	int iterations = 200;
	double* aRates = new double[4]{ get_ab_rate(true, true, dmu, f), get_ab_rate(true, false, dmu, f), get_ab_rate(false, true, dmu, f), get_ab_rate(false, false, dmu, f) };
	double* bRates = new double[4]{ get_ba_rate(true, true, dmu, f), get_ba_rate(true, false, dmu, f), get_ba_rate(false, true, dmu, f), get_ba_rate(false, false, dmu, f) };
	double aEsc;
	double bEsc;
	//to be used by gillespie alg
	double* aCDF = create_discr_cdf(aRates, 4, aEsc);
	double* bCDF = create_discr_cdf(bRates, 4, bEsc);

	for (int j = 0; j < epochs; j++)
	{
		//move < 2 <=> n->n+1
		//odd move <=> y->y
		
		int* x = new int[iterations];
		int* y = new int[iterations];
		double* t = new double[iterations];
		x[0] = 0;
		y[0] = 0;
		t[0] = 0;
		srand(time(NULL));
		double u;
		/*
		for (int i = 1; i < iterations; i++)
		{
			bool excited = x[i - 1] % 2 == 1;
			u = uniform_sample();
			if (excited)
			{
				//b site with energy epsAB
				t[i] = t[i - 1] + exp_cdf_inv(u, 1 / bEsc);
				u = uniform_sample();
				int move = sample_discr_cdf(bCDF, 4, u);
				if (move < 2)
				{
					x[i] = x[i - 1] + 1;
				}
				else
				{
					x[i] = x[i - 1] - 1;
				}
				if (move % 2 == 0)
				{
					y[i] = y[i - 1] - 1;
				}
				else
				{
					y[i] = y[i - 1];
				}
			}
			else
			{
				t[i] = t[i - 1] + exp_cdf_inv(u, 1 / aEsc);
				u = uniform_sample();
				int move = sample_discr_cdf(aCDF, 4, u);

				if (move < 2)
				{
					x[i] = x[i - 1] + 1;
				}
				else
				{
					x[i] = x[i - 1] - 1;
				}
				if (move % 2 == 0)
				{
					y[i] = y[i - 1] + 1;
				}
				else
				{
					y[i] = y[i - 1];
				}
			}
		}
		*/
		for (int i = 1; i < iterations; i++)
		{
			bool excited = x[i - 1] % 2 == 1;
			u = uniform_sample();
			if (excited)
			{
				int move = first_reaction(bRates, 4, bEsc, t[i]);
				t[i] += t[i - 1];
				if (move < 2)
				{
					x[i] = x[i - 1] + 1;
				}
				else
				{
					x[i] = x[i - 1] - 1;
				}
				if (move % 2 == 0)
				{
					y[i] = y[i - 1] - 1;
				}
				else
				{
					y[i] = y[i - 1];
				}
			}
			else
			{
				int move = first_reaction(aRates, 4, aEsc, t[i]);
				t[i] += t[i - 1];;

				if (move < 2)
				{
					x[i] = x[i - 1] + 1;
				}
				else
				{
					x[i] = x[i - 1] - 1;
				}
				if (move % 2 == 0)
				{
					y[i] = y[i - 1] + 1;
				}
				else
				{
					y[i] = y[i - 1];
				}
			}
		}
		/*
		for (int i = 0; i < iterations; i++)
		{
			cout << t[i];
			cout << "	";
			cout << x[i];
			cout << "	";
			cout << y[i];
			cout << "\r\n";
		}
		*/
		v_i[j] = d*mean_velocity(x, t, iterations);
		r_i[j] = mean_velocity(y, t, iterations);
		delete x;
		delete y;
		delete t;
	}
	double mv = mean(v_i, epochs);
	double mr = mean(r_i, epochs);
	cout << mv;
	cout << "\n\r";
	cout << mr;
	cout << "\n\r";
	cout << (-mv*f) / (mr*dmu*d);
	system("PAUSE");
	main();
    return 0;
}


