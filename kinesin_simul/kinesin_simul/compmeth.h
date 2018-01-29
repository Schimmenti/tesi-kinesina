#pragma once
#include "stdafx.h"


double forward_op(double* v, int startingIndex, int k)
{
	if (k == 1)
	{
		return v[startingIndex + 1] - v[startingIndex];
	}
	else
	{
		return (forward_op(v, startingIndex + 1, k - 1) - forward_op(v, startingIndex, k - 1));
	}
}

