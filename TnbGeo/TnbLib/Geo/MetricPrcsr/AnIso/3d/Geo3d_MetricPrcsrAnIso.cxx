#include <Geo3d_MetricPrcsrAnIso.hxx>

#include <Geo_SegmentIntegrand.hxx>
#include <Geo_SegmentIntegrand_Function.hxx>
#include <NumAlg_AdaptiveInteg.hxx>

namespace tnbLib
{

	typedef Geo_SegmentIntegrand_Function<Geo3d_MetricPrcsrAnIso, true>
		Geo3d_SegmentIntegrand_UnitLength_Function;
	typedef Geo_SegmentIntegrand_Function<Geo3d_MetricPrcsrAnIso, false>
		Geo3d_SegmentIntegrand_Function;
	typedef Geo_SegmentIntegrand<Geo3d_MetricPrcsrAnIso> Geo3d_SegmentIntegrand;

	template<>
	Standard_Real Geo3d_MetricPrcsrAnIso::CalcDistance
	(
		const Pnt3d& theP0,
		const Pnt3d& theP1
	) const
	{
		Geo3d_SegmentIntegrand line(theP0, theP1, *this);
		Geo3d_SegmentIntegrand_Function func(line);

		Debug_Null_Pointer(base::Info()->IntegInfo());
		auto& inf = *base::Info()->IntegInfo();

		NumAlg_AdaptiveInteg<Geo3d_SegmentIntegrand_Function> alg(func, 0.0, 1.0, inf);
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

	template<>
	Standard_Real Geo3d_MetricPrcsrAnIso::CalcUnitDistance
	(
		const Pnt3d& theP0,
		const Pnt3d& theP1
	) const
	{
		Geo3d_SegmentIntegrand line(theP0, theP1, *this);
		Geo3d_SegmentIntegrand_UnitLength_Function func(line);

		Debug_Null_Pointer(base::Info()->IntegInfo());
		auto& inf = *base::Info()->IntegInfo();

		NumAlg_AdaptiveInteg<Geo3d_SegmentIntegrand_UnitLength_Function> alg(func, 0.0, 1.0, inf);
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
}