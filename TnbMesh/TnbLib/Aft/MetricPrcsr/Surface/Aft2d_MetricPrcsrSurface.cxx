#include <Aft2d_MetricPrcsrSurface.hxx>

#include <Entity2d_Eigen.hxx>
#include <Entity2d_Metric1.hxx>

namespace tnbLib
{
	template<>
	Entity2d_Box
		Aft2d_MetricPrcsrSurface::CalcSearchRegion
		(
			const Standard_Real theRadius,
			const Entity2d_Metric1& theMetric,
			const Pnt2d& theCentre
		) const
	{
		auto& eigen = *mesh2d_aft_metric_prcsr_eigen_calculator;

		const auto c = (Standard_Real)1.0 / (theRadius*theRadius);
		eigen.CalcEigen(c*theMetric);

		const auto dQd = eigen.H2()*eigen.E2();
		const auto dQr = eigen.H1()*eigen.E1();

		const auto Qd = theCentre - dQd;
		const auto Qu = theCentre + dQd;

		static std::vector<Pnt2d> Pts(4);
		Pts[0] = Qd + dQr;
		Pts[1] = Qu + dQr;
		Pts[2] = Qu - dQr;
		Pts[3] = Qd - dQr;

		const auto box = Entity2d_Box::BoundingBoxOf(Pts);
		return std::move(box);
	}

	template<>
	Entity2d_Box Aft2d_MetricPrcsrSurface::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeSurface& theEdge
	) const
	{
		auto mp =
			base::CalcEffectiveMetric(theEdge.Centre(), theCentre);

		const auto& n0 = *theEdge.Node0();
		const auto& n1 = *theEdge.Node1();

		const auto& m0 = n0.Metric();
		const auto& m1 = n1.Metric();

		auto m = Entity2d_Metric1::UnionSR(mp, Entity2d_Metric1::UnionSR(m0, m1));
		m *= (1.0 / (theRadius*theRadius));

		auto& eigen = *mesh2d_aft_metric_prcsr_eigen_calculator;
		eigen.CalcEigen(m);

		const auto dQd = eigen.H2()*eigen.E2();
		const auto dQr = eigen.H1()*eigen.E1();

		const auto Qd = theCentre - dQd;
		const auto Qu = theCentre + dQd;

		static std::vector<Pnt2d> Pts(4);
		Pts[0] = Qd + dQr;
		Pts[1] = Qu + dQr;
		Pts[2] = Qu - dQr;
		Pts[3] = Qd - dQr;

		const auto box = Entity2d_Box::BoundingBoxOf(Pts);
		return std::move(box);
	}

	template<>
	Entity2d_Box Aft2d_MetricPrcsrSurface::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Aft2d_EdgeSurface& theEdge
	) const
	{
		const auto& n0 = *theEdge.Node0();
		const auto& n1 = *theEdge.Node1();

		const auto& m0 = n0.Metric();
		const auto& m1 = n1.Metric();

		auto m = Entity2d_Metric1::UnionSR(m0, m1);
		m *= (1.0 / (theRadius*theRadius));

		auto& eigen = *mesh2d_aft_metric_prcsr_eigen_calculator;
		eigen.CalcEigen(m);

		eigen.CalcEigen(m);

		auto dQd = eigen.H2()*eigen.E2();
		auto dQr = eigen.H1()*eigen.E1();

		const auto& centre = theEdge.Centre();

		auto Qd = centre - dQd;
		auto Qu = centre + dQd;

		static std::vector<Pnt2d> Pts(4);
		Pts[0] = Qd + dQr;
		Pts[1] = Qu + dQr;
		Pts[2] = Qu - dQr;
		Pts[3] = Qd - dQr;

		auto box = Entity2d_Box::BoundingBoxOf(Pts);
		return std::move(box);
	}

	template<>
	Entity2d_Box Aft2d_MetricPrcsrSurface::CalcEffectiveFront
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeSurface& /*theEdge*/
	) const
	{
		static std::vector<Pnt2d> Pts(4);

		Pts[0] = theCentre - Pnt2d(0, theRadius);
		Pts[1] = theCentre + Pnt2d(theRadius, 0);
		Pts[2] = theCentre + Pnt2d(0, theRadius);
		Pts[3] = theCentre - Pnt2d(theRadius, 0);

		Pts[0] = CorrEffRegion(theCentre, Pts[0], theRadius);
		Pts[1] = CorrEffRegion(theCentre, Pts[1], theRadius);
		Pts[2] = CorrEffRegion(theCentre, Pts[2], theRadius);
		Pts[3] = CorrEffRegion(theCentre, Pts[3], theRadius);

		auto box = Entity2d_Box::BoundingBoxOf(Pts);
		return std::move(box);
	}
}