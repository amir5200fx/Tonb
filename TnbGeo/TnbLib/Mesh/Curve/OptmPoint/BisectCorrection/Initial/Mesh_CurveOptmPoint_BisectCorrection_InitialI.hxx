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

	Standard_Boolean setX0 = Standard_False;
	Standard_Boolean setX1 = Standard_False;
	Standard_Real x0 = 0;
	Standard_Real x1 = 0;

	forThose(Iter, 1, MaxLevel())
	{
		auto dis = map.CalcUnitDistance(P0, curve.Value(Correct)) / Len();
		if (dis < 1.0)
		{
			setX0 = Standard_True;
			x0 = Correct;
		}
		if (dis > 1.0)
		{
			setX1 = Standard_True;
			x1 = Correct;
		}
		auto du = (Correct - Umin) / dis;

		Correct = Umin + du;

		if (Correct < Umin) Correct = Umin;
		if (Correct > Umax) Correct = Umax;

		if (setX0 AND setX1)
		{
			break;
		}
	}
	auto t = std::make_pair(x0, x1);
	BoundRef() = std::move(t);

	Change_IsDone() = Standard_True;
}