#pragma once
#include <Global_Macros.hxx>
template<class gCurveType, class MetricPrcsrType>
inline void tnbLib::Mesh_CurveOptmPoint_BisectCorrection_Initial<gCurveType, MetricPrcsrType>::Perform()
{
	const auto& map = Entity().SizeMap();
	const auto& curve = Entity().Curve();

	auto Correct = Guess();
	auto P0 = curve.Value(U0());

	auto Umin = U0();
	auto Umax = Entity().LastParameter();

	if (Correct < Umin) Correct = Umin;
	if (Correct > Umax) Correct = Umax;

	Standard_Real x0 = 0;
	Standard_Real x1 = 0;

	Standard_Boolean converged = Standard_False;
	auto dis = map.CalcUnitDistance(P0, curve.Value(Correct)) / Len();
	if (dis > 1.0)
	{
		x1 = Correct;
		auto du = x1 - Umin;
		forThose(Iter, 1, MaxLevel())
		{
			du *= 0.5;
			x0 = Umin + du;
			auto dis1 = map.CalcUnitDistance(P0, curve.Value(x0)) / Len();
			if (dis1 < 1.0)
			{
				converged = Standard_True;
				break;
			}
		}
	}
	else if (dis < 1.0)
	{
		x0 = Correct;
		auto du = x0 - Umin;
		forThose(Iter, 1, MaxLevel())
		{
			du *= 2.0;
			x1 = Umin + du;
			if (x1 > Umax) x1 = Umax;
			auto dis1 = map.CalcUnitDistance(P0, curve.Value(x1)) / Len();
			if (dis1 > 1.0)
			{
				converged = Standard_True;
				break;
			}
		}
	}
	else
	{
		x0 = x1 = Guess();
		converged = Standard_True;
	}

	auto t = std::make_pair(x0, x1);
	BoundRef() = std::move(t);
	IsConverged_ = converged;

	Change_IsDone() = Standard_True;
}