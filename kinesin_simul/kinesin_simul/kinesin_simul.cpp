// kinesin_simul.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include "master_eq_ssa.h"
#include "kinesin.h"
#include <iostream>
using namespace std;
int main()
{
	double f = -4;
	double dmu = 3.5;
	int iterations = 100;
	//move < 2 <=> n->n+1
	//odd move <=> y->y
	double* aRates = new double[4]{ get_ab_rate(true, true, dmu, f), get_ab_rate(true, false, f, dmu), get_ab_rate(false, true, dmu, f), get_ab_rate(false, false, dmu, f) };
	double* bRates = new double[4]{ get_ba_rate(true, true, dmu, f), get_ba_rate(true, false, f, dmu), get_ba_rate(false, true, dmu, f), get_ba_rate(false, false, dmu, f) };
	double aEsc;
	double bEsc;
	//to be used by gillespie alg
	double* aCDF = create_discr_cdf(aRates, 4, aEsc);
	double* bCDF = create_discr_cdf(bRates, 4, bEsc);


	system("PAUSE");
    return 0;
}


