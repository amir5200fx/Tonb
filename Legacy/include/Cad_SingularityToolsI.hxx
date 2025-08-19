#pragma once
#include <Cad_PoleSingularCurve.hxx>
#include <Entity2d_Polygon.hxx>
#include <Cad_SingularCurveTraits.hxx>
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
			auto geom = GetParaCurve(pts.at(0), pts.at(1));
			Debug_Null_Pointer(geom);

			auto pCurve = 
				std::make_shared
				<typename cad_singular_curve_traits<CurveType>::baseCurveType>(std::move(geom));
			Debug_Null_Pointer(pCurve);

			auto curve = std::make_shared<Cad_PoleSingularCurve<CurveType>>(std::move(pCurve));
			return std::move(curve);
		}
		else
		{
			auto geom = GetParaCurve(pts);
			Debug_Null_Pointer(geom);

			auto pCurve =
				std::make_shared
				<typename cad_singular_curve_traits<CurveType>::baseCurveType>(std::move(geom));
			Debug_Null_Pointer(pCurve);

			auto curve = std::make_shared<Cad_PoleSingularCurve<CurveType>>(std::move(pCurve));
			return std::move(curve);
		}
	}
}