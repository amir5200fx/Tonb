#include <EberlyLib.hxx>

void tnbLib::EberlyLib::ComputeIntersection
(
	double b,
	double f00,
	double f10,
	double sValue[2],
	int classify[2],
	int edge[2],
	double end[2][2]
)
{
	if (classify[0] < 0)
	{
		edge[0] = 0;
		end[0][0] = 0;
		end[0][1] = f00 / b;
		if (end[0][1] < 0 || end[0][1] > 1)
		{
			end[0][1] = 0.5;
		}

		if (classify[1] == 0)
		{
			edge[1] = 3;
			end[1][0] = sValue[1];
			end[1][1] = 1;
		}
		else
		{
			edge[1] = 1;
			end[1][0] = 1;
			end[1][1] = f10 / b;
			if (end[1][1] < 0 || end[1][1] > 1)
			{
				end[1][1] = 0.5;
			}
		}
	}
	else if (classify[0] == 0)
	{
		edge[0] = 2;
		end[0][0] = sValue[0];
		end[0][1] = 0;

		if (classify[1] < 0)
		{
			edge[1] = 0;
			end[1][0] = 0;
			end[1][1] = f00 / b;
			if (end[1][1] < 0 || end[1][1] > 1)
			{
				end[1][1] = 0.5;
			}
		}
		else if (classify[1] == 0)
		{
			edge[1] = 3;
			end[1][0] = sValue[1];
			end[1][1] = 1;
		}
		else
		{
			edge[1] = 1;
			end[1][0] = 1;
			end[1][1] = f10 / b;
			if (end[1][1] < 0 || end[1][1] > 1)
			{
				end[1][1] = 0.5;
			}
		}
	}
	else
	{
		edge[0] = 1;
		end[0][0] = 1;
		end[0][1] = f10 / b;
		if (end[0][1] < 0 || end[0][1] > 1)
		{
			end[0][1] = 0.5;
		}

		if (classify[1] == 0)
		{
			edge[1] = 3;
			end[1][0] = sValue[1];
			end[1][1] = 1;
		}
		else
		{
			edge[1] = 0;
			end[1][0] = 0;
			end[1][1] = f00 / b;
			if (end[1][1] < 0 || end[1][1] > 1)
			{
				end[1][1] = 0.5;
			}
		}
	}
}

void tnbLib::EberlyLib::ComputeMinimumParameters
(
	double b,
	double c, 
	double e,
	double g00, 
	double g10,
	double g01, 
	double g11,
	int edge[2],
	double end[2][2], 
	double parameter[2]
)
{
	double delta = end[1][1] - end[0][1];
	double h0 = delta * (-b * end[0][0] + c * end[0][1] - e);
	if (h0 >= 0)
	{
		if (edge[0] == 0)
		{
			parameter[0] = 0;
			parameter[1] = GetClampedRoot(c, g00, g01);
		}
		else if (edge[0] == 1)
		{
			parameter[0] = 1;
			parameter[1] = GetClampedRoot(c, g10, g11);
		}
		else
		{
			parameter[0] = end[0][0];
			parameter[1] = end[0][1];
		}
	}
	else
	{
		double h1 = delta * (-b * end[1][0] + c * end[1][1] - e);
		if (h1 <= 0)
		{
			if (edge[1] == 0)
			{
				parameter[0] = 0;
				parameter[1] = GetClampedRoot(c, g00, g01);
			}
			else if (edge[1] == 1)
			{
				parameter[0] = 1;
				parameter[1] = GetClampedRoot(c, g10, g11);
			}
			else
			{
				parameter[0] = end[1][0];
				parameter[1] = end[1][1];
			}
		}
		else
		{
			double z = std::min(h0 / (h0 - h1), 1.0);
			z = std::max(z, 0.0);
			double omz = 1 - z;
			parameter[0] = omz * end[0][0] + z * end[1][0];
			parameter[1] = omz * end[0][1] + z * end[1][1];
		}
	}
}

void tnbLib::EberlyLib::CSMain
(
	const Segment& segment0,
	const Segment& segment1,
	Result& result
)
{
	Pnt3d P0 = segment0.end0;
	Pnt3d P1 = segment0.end1;
	Pnt3d Q0 = segment1.end0;
	Pnt3d Q1 = segment1.end1;

	Pnt3d P1mP0 = P1 - P0;
	Pnt3d Q1mQ0 = Q1 - Q0;
	Pnt3d P0mQ0 = P0 - Q0;
	double a = DotProduct(P1mP0, P1mP0);
	double b = DotProduct(P1mP0, Q1mQ0);
	double c = DotProduct(Q1mQ0, Q1mQ0);
	double d = DotProduct(P1mP0, P0mQ0);
	double e = DotProduct(Q1mQ0, P0mQ0);

	double f00 = d;
	double f10 = f00 + a;
	double f01 = f00 - b;
	double f11 = f10 - b;
	double g00 = -e;
	double g01 = g00 + c;
	double g10 = g00 - b;
	double g11 = g10 + c;

	if (a > 0 && c > 0)
	{
		double sValue[2];
		sValue[0] = GetClampedRoot(a, f00, f10);
		sValue[1] = GetClampedRoot(a, f01, f11);

		int classify[2];
		for (int i = 0; i < 2; ++i)
		{
			if (sValue[i] <= 0)
			{
				classify[i] = -1;
			}
			else if (sValue[i] >= 1)
			{
				classify[i] = 1;
			}
			else
			{
				classify[i] = 0;
			}
		}

		if (classify[0] == -1 && classify[1] == -1)
		{
			result.parameter[0] = 0;
			result.parameter[1] = GetClampedRoot(c, g00, g01);
		}
		else if (classify[0] == 1 && classify[1] == 1)
		{
			result.parameter[0] = 1;
			result.parameter[1] = GetClampedRoot(c, g10, g11);
		}
		else
		{
			int edge[2];
			double end[2][2];
			ComputeIntersection(b, f00, f10, sValue, classify, edge, end);
			ComputeMinimumParameters(b, c, e, g00, g10, g01, g11,
				edge, end, result.parameter);
		}
	}
	else
	{
		if (a > 0)
		{
			result.parameter[0] = GetClampedRoot(a, f00, f10);
			result.parameter[1] = 0;
		}
		else if (c > 0)
		{
			result.parameter[0] = 0;
			result.parameter[1] = GetClampedRoot(c, g00, g01);
		}
		else
		{
			result.parameter[0] = 0;
			result.parameter[1] = 0;
		}
	}

	Pnt3d closest0 = (1 - result.parameter[0]) * P0 + result.parameter[0] * P1;
	Pnt3d closest1 = (1 - result.parameter[1]) * Q0 + result.parameter[1] * Q1;
	Pnt3d diff = closest0 - closest1;
	result.sqrDistance = DotProduct(diff, diff);
#if GET_CLOSEST
	result.closest[0] = closest0;
	result.closest[1] = closest1;
#endif
}