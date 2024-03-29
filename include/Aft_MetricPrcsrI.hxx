#pragma once
#include <MeshBase_Tools.hxx>
#include <Global_Macros.hxx>
#include <Geo_Tools.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>
namespace tnbLib
{

	template<class FrontType, class SizeFun, class MetricFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::Point
		Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::CorrEffRegion
		(
			const Point & theCentre,
			const Point & theP,
			const Standard_Real theRadius
		) const
	{
		const auto nbIters = Info()->NbIters();
		const auto tol = Info()->Tolerance();

		const auto& domain = this->BoundingBox();
		auto P = theP;
		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
		}
		forThose(Iter, 1, nbIters)
		{
			auto d = CalcDistance(theCentre, P) / theRadius;
			if (d <= gp::Resolution())
			{
				return theP;
			}
			P = theCentre + (1.0 / d)*(P - theCentre);
			if (NOT domain.IsInside(P))
			{
				P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
			}

			if (std::abs(1.0- d) <= tol)
			{
				break;
			}
		}

		return std::move(P);
	}

	template<class FrontType, class SizeFun, class MetricFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::Oriented
	(
		const Point & thePt,
		const frontType & theFront
	) const
	{
		return theFront.Oriented(thePt);
	}

	template<class FrontType, class SizeFun, class MetricFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::CalcDistance
	(
		const Point & thePt,
		const frontType & theFront
	) const
	{
		const auto& p0 = theFront.Node0()->Coord();
		const auto& p1 = theFront.Node1()->Coord();
		const auto pt = Geo_Tools::ProjectPtAtSegment(thePt, p0, p1);
		return base::CalcDistance(thePt, pt);
	}

	template<class FrontType, class SizeFun, class MetricFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::CalcSquareDistance
	(
		const Point & thePt,
		const frontType & theFront
	) const
	{
		const auto& p0 = theFront.Node0()->Coord();
		const auto& p1 = theFront.Node1()->Coord();
		const auto pt = Geo_Tools::ProjectPtAtSegment(thePt, p0, p1);
		return base::CalcSquareDistance(thePt, pt);
	}

	template<class FrontType, class SizeFun, class MetricFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::CalcElementSize
	(
		const std::shared_ptr<frontType>& theFront
	) const
	{
		Debug_Null_Pointer(theFront);
		return base::CalcElementSize(theFront->Centre());
	}

	template<class FrontType, class SizeFun, class MetricFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::Point
		Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::CalcCentreOf
		(
			const frontType & theFront
		) const
	{
		auto cp = theFront.Centre();
		return std::move(cp);
	}

	/*template<class FrontType, class SizeFun, class MetricFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::metricType
		Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>::CalcEffectiveMetric
		(
			const Point & theP0,
			const Point & theP1
		) const
	{
		const auto nbSamples = Info()->NbSamples();
		if (nbSamples IS_EQUAL 1)
		{
			auto m = base::CalcMetric(MEAN(theP0, theP1));
			const auto dP = theP1 - theP0;

			const auto d = base::CalcDistance(theP0, theP1);
			const auto landa = d / DotProduct(dP, m.Multiplied(dP));

			m *= (landa*landa);
			return std::move(m);
		}

		const auto du = 1.0 / (Standard_Real)nbSamples;
		const auto dP = theP1 - theP0;
		const auto dPu = dP * du;

		std::vector<metricType> metrics;
		metrics.reserve(nbSamples);
		forThose(Index, 1, nbSamples)
		{
			auto P = dPu * Index + theP0 - 0.5*dPu;

			auto m = base::CalcMetric(P);
			metrics.push_back(std::move(m));
		}

		auto ms = metrics[0];
		forThose(Index, 1, metrics.size() - 1)
		{
			ms = metricType::IntersectionSR(ms, metrics[Index]);
		}

		const auto d = CalcDistance(theP0, theP1);
		const auto landa = d / metricType::Distance(theP0, theP1, ms);

		ms *= (landa*landa);
		return std::move(ms);
	}*/

}

namespace tnbLib
{

	template<class FrontType, class SizeFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, void>::Oriented
	(
		const Point & thePt,
		const frontType & theFront
	) const
	{
		return theFront.Oriented(thePt);
	}

	template<class FrontType, class SizeFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcDistance
	(
		const Point & thePt,
		const frontType & theFront
	) const
	{
		return theFront.CalcDistance(thePt);
	}

	template<class FrontType, class SizeFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcSquareDistance
	(
		const Point & thePt,
		const frontType & theFront
	) const
	{
		return theFront.CalcSquareDistance(thePt);
	}

	template<class FrontType, class SizeFun>
	Standard_Real Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcElementSize
	(
		const std::shared_ptr<frontType>& theFront
	) const
	{
		Debug_Null_Pointer(theFront);
		return base::CalcElementSize(theFront->Centre());
	}

	template<class FrontType, class SizeFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, void>::Point
		Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcCentreOf
		(
			const frontType & theFront
		) const
	{
		auto cp = theFront.Centre();
		return std::move(cp);
	}

	template<class FrontType, class SizeFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, void>::box
		Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcSearchRegion
		(
			const Standard_Real theRadius,
			const Point & theCentre
		) const
	{
		auto b = box(theCentre - theRadius, theCentre + theRadius);
		return std::move(b);
	}

	template<class FrontType, class SizeFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, void>::box
		Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcSearchRegion
		(
			const Standard_Real theRadius,
			const Point & theCentre,
			const frontType & /*theFront*/
		) const
	{
		auto b = box(theCentre - theRadius, theCentre + theRadius);
		return std::move(b);
	}

	template<class FrontType, class SizeFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, void>::box
		Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcSearchRegion
		(
			const Standard_Real theRadius,
			const frontType & theFront
		) const
	{
		auto b = CalcSearchRegion(theRadius, theFront.Centre());
		return std::move(b);
	}

	template<class FrontType, class SizeFun>
	typename Aft_MetricPrcsr<FrontType, SizeFun, void>::box
		Aft_MetricPrcsr<FrontType, SizeFun, void>::CalcEffectiveFront
		(
			const Standard_Real theRadius,
			const Point & theCentre,
			const frontType & /*theFront*/
		) const
	{
		auto b = box(theCentre - theRadius, theCentre + theRadius);
		return std::move(b);
	}
}