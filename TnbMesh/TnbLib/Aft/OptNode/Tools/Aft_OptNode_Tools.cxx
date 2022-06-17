#include <Aft_OptNode_Tools.hxx>

#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <MeshBase_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>

std::tuple<tnbLib::Pnt2d, tnbLib::Pnt2d, Standard_Boolean> 
tnbLib::Aft_OptNode_Tools::BisectInitialGuess
(
	const Geo2d_MetricPrcsrAnIso& theMetricMap,
	const Pnt2d & theP0, 
	const Pnt2d & theGuess,
	const Standard_Real h,
	const Standard_Integer theMaxLev
)
{
	Debug_If_Condition(h < gp::Resolution());
	static const Standard_Real One = 1.0;
	const auto d = theMetricMap.CalcUnitDistance(theP0, theGuess) / h;
	std::cout << std::endl;
	std::cout << "d= " << d << std::endl;
	const auto& domain = theMetricMap.BoundingBox();
	if (d < One)
	{
		auto p0 = theP0;
		Standard_Real s = 2.0;
		for (auto Iter = 1; Iter <= theMaxLev; Iter++)
		{
			auto p = p0 + (theGuess - p0)*s;
			if (NOT domain.IsInside(p))
			{
				p = MeshBase_Tools::CorrectCoord(theP0, p, domain);
			}
			auto di = theMetricMap.CalcUnitDistance(theP0, p) / h;
			std::cout << "di : " << di << std::endl;
			if (di > One)
			{
				auto t = std::make_tuple(std::move(p0), std::move(p), Standard_True);
				return std::move(t);
			}
			s *= 2.0;
		}
		auto t = std::make_tuple(p0, p0, Standard_False);
		return std::move(t);
	}
	else if (d > One)
	{
		auto p1 = theP0;
		Standard_Real s = 0.5;
		for (auto Iter = 1; Iter <= theMaxLev; Iter++)
		{
			auto p = theP0 + (theGuess - theP0)*s;
			auto di = theMetricMap.CalcUnitDistance(theP0, p) / h;
			std::cout << "di : " << di << std::endl;
			if (di < One)
			{
				auto t = std::make_tuple(std::move(p), std::move(p1), Standard_True);
				return std::move(t);
			}
			s *= 0.5;
		}
		auto t = std::make_tuple(p1, p1, Standard_False);
		return std::move(t);
	}
	else
	{
		auto t = std::make_tuple(theP0, theP0, Standard_True);
		return std::move(t);
	}
}