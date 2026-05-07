#include <Geo2d_MetricPrcsrUniMetric.hxx>

#include <Geo_SegmentIntegrand.hxx>
#include <Geo_SegmentIntegrand_Function.hxx>
#include <NumAlg_AdaptiveInteg.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef Geo_SegmentIntegrand_Function<Geo2d_MetricPrcsrUniMetric, true>
		Geo2d_SegmentIntegrand_UnitLength_Function;
	typedef Geo_SegmentIntegrand_Function<Geo2d_MetricPrcsrUniMetric, false>
		Geo2d_SegmentIntegrand_Function;
	typedef Geo_SegmentIntegrand<Geo2d_MetricPrcsrUniMetric> Geo2d_SegmentIntegrand;
}

template<>
Standard_Real tnbLib::Geo2d_MetricPrcsrUniMetric::CalcDistance
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	Debug_Null_Pointer(MetricFunction());
	const auto& m = MetricFunction()->Metric();

	return Entity2d_Metric1::Distance(theP0, theP1, m);
}

template<>
Standard_Real tnbLib::Geo2d_MetricPrcsrUniMetric::CalcUnitDistance
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	Geo2d_SegmentIntegrand line(theP0, theP1, *this);
	Geo2d_SegmentIntegrand_UnitLength_Function func(line);

	Debug_Null_Pointer(base::Info());
	Debug_Null_Pointer(base::Info()->IntegInfo());
	auto& inf = *base::Info()->IntegInfo();

	NumAlg_AdaptiveInteg<Geo2d_SegmentIntegrand_UnitLength_Function> alg(func, 0.0, 1.0, inf);
	alg.Perform();

	Debug_If_Condition_Message(NOT alg.IsDone(), "Integration has not been performed");

	if (NOT inf.IsConverged())
	{
		FatalConvErrorIn(FunctionSIG, inf.MaxNbIterations(), inf.Tolerance())
			<< "Algorithm is not converged!" << endl
			<< abort(FatalConvError);
	}
	return inf.Result();
}