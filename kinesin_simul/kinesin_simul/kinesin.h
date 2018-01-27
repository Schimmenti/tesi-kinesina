#pragma once

const double d = 4E-9;
const double k0_ATP = 1.4E+5; //milliMoles^-1
const double epsAB = 10.81; // dE = E_B - E_A
//rates
const double ALPHA_RATE = 0.57;
const double ALPHA_P_RATE = 1.3e-6;
const double OMEGA_RATE = 3.5;
const double OMEGA_P_RATE = 108.15;
//form factors
const double FF_A_PLUS = 0.25;
const double FF_A_MINUS = 1.83;
const double FF_B_PLUS = 0.08;
const double FF_B_MINUS = -0.16;
const double kB = 1.38064852E-23;

double normalize_pico_force(double pNForce, double temperature)
{
	return pNForce*1E-12*d / (kB*temperature);
}
double normalize_chem(double atpMilliMoles)
{
	return log(k0_ATP*atpMilliMoles);
}
double get_ab_rate(bool right, bool consumeAtp, double dMu, double f)
{
	if (consumeAtp & right)
	{
		return ALPHA_RATE * exp(-epsAB + dMu + FF_A_PLUS * f); //consume and against force -> for negative f lowers
	}
	else if (consumeAtp & !right)
	{
		return ALPHA_P_RATE * exp(-epsAB + dMu - FF_A_MINUS * f); //consume and towards force -> for negative f highers
	}
	else if (!consumeAtp & right)
	{
		return OMEGA_RATE * exp(-epsAB + FF_A_PLUS*f); //no consume and against force -> for negative f lowers
	}
	else
	{
		return OMEGA_P_RATE * exp(-epsAB - FF_A_MINUS * f); //no consume and towards force -> for negative f highers
	}
}
double get_ba_rate(bool right, bool produceAtp, double dMu, double f)
{
	if (produceAtp & right)
	{
		return ALPHA_P_RATE * exp(FF_B_PLUS*f); //for negative f lowers DR
	}
	else if (produceAtp & !right)
	{
		return ALPHA_RATE * exp(-FF_B_MINUS*f); //for negative f highers DL
	}
	else if (!produceAtp & right)
	{
		return OMEGA_P_RATE * exp(FF_B_PLUS*f); //for negative f lowers BA-R
	}
	else
	{
		return OMEGA_RATE * exp(-FF_B_MINUS * f); //for negative f highers BA-L
	}
}