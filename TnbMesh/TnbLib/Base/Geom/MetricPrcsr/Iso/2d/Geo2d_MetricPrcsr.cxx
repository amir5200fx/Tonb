#include <Geo2d_MetricPrcsr.hxx>

#include <Geo_SegmentIntegrand.hxx>
#include <Geo_SegmentIntegrand_Function.hxx>
#include <Geo_MetricPrcsr_Info.hxx>
#include <NumAlg_AdaptiveInteg.hxx>

const std::string tnbLib::Geo2d_MetricPrcsr::extension = ".mprcsr2d";

namespace tnbLib
{

	typedef Geo_SegmentIntegrand_Function<Geo2d_MetricPrcsr, true>
		Geo2d_SegmentIntegrand_Function;
	typedef Geo_SegmentIntegrand<Geo2d_MetricPrcsr> Geo2d_SegmentIntegrand;

	template<>
	Standard_Real Geo2d_MetricPrcsr::CalcUnitDistance
	(
		const Pnt2d& theP0,
		const Pnt2d& theP1
	) const
	{
		Geo2d_SegmentIntegrand line(theP0, theP1, *this);
		Geo2d_SegmentIntegrand_Function func(line);

		Debug_Null_Pointer(base::Info());
		Debug_Null_Pointer(base::Info()->IntegInfo());
		auto& inf = *base::Info()->IntegInfo();

		NumAlg_AdaptiveInteg<Geo2d_SegmentIntegrand_Function> alg(func, 0.0, 1.0, inf);
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