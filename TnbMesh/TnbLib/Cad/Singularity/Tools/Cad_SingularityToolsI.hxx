#pragma once
#include <Cad_PoleSingularCurve.hxx>
#include <Entity2d_Polygon.hxx>
namespace tnbLib
{

	template<class CurveType>
	inline std::shared_ptr<Cad_PoleSingularCurve<CurveType>> 
		Cad_SingularityTools::ParametricPoleCurve(const Entity2d_Polygon & thePoly)
	{
#ifdef _DEBUG
		Entity2d_Polygon::Check(thePoly);
#endif // _DEBUG
		const auto& pts = thePoly.Points();
		if (thePoly.NbPoints() IS_EQUAL 2)
		{			
			auto pCurve = GetParaCurve(pts.at(0), pts.at(1));

			auto curve = std::make_shared<Cad_PoleSingularCurve<CurveType>>(std::move(pCurve));
			return std::move(curve);
		}
		else
		{
			auto pCurve = GetParaCurve(pts);
			auto curve = std::make_shared<Cad_PoleSingularCurve<CurveType>>(std::move(pCurve));
			return std::move(curve);
		}
	}
}