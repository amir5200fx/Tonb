#pragma once
namespace tnbLib
{

	template<class StbFun>
	Standard_Real hydStcLib::StbFun_IntgFun<StbFun>::Value
	(
		const Standard_Real x
	) const
	{
		const auto minH = Entity().MinHeel();
		const auto maxH = Entity().MaxHeel();

		auto p = x;
		if (p < minH) p = minH;
		if (p > maxH) p = maxH;

		return Entity().Value(p) - Y0();
	}
}