#pragma once
inline double 
tnbLib::EberlyLib::GetClampedRoot
(
	double slope,
	double h0,
	double h1
)
{
	double r;
	if (h0 < 0)
	{
		if (h1 > 0)
		{
			r = -h0 / slope;
			if (r > 1)
			{
				r = 0.5;
			}
		}
		else
		{
			r = 1;
		}
	}
	else
	{
		r = 0;
	}
	return r;
}
