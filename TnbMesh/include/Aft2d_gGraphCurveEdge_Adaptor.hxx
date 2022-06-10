#pragma once
#ifndef _Aft2d_gGraphCurveEdge_Adaptor_Header
#define _Aft2d_gGraphCurveEdge_Adaptor_Header

#include <Geo_GraphEdgeAdaptor.hxx>
#include <Aft2d_gGraphCurveEdge_Traits.hxx>
#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

#include <memory>

namespace tnbLib
{

	template<>
	class Geo_GraphEdgeAdaptor<Aft2d_gGraphCurveEdge_Traits>
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_gPlnCurveSurface> theCurve_;

	protected:

		// default constructor [6/4/2022 Amir]

		Geo_GraphEdgeAdaptor()
		{}

		// constructors [6/4/2022 Amir]


	public:

		const auto& Curve() const
		{
			return theCurve_;
		}

		void SetCurve(const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve)
		{
			theCurve_ = theCurve;
		}
	};
}

#endif // !_Aft2d_gGraphCurveEdge_Adaptor_Header
