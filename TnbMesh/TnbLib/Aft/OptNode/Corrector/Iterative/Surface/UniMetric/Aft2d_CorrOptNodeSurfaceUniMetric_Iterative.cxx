#include <Aft2d_CorrOptNodeSurfaceUniMetric_Iterative.hxx>

#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Aft2d_CorrOptNodeSurfaceUniMetric_Iterative::verbose(0);

template<>
void tnbLib::Aft2d_CorrOptNodeSurfaceUniMetric_Iterative::Perform
(
	const Aft_SizeCorr_IterativeInfo& theInfo
)
{
	Debug_Null_Pointer(MetricMap());
	Debug_Null_Pointer(Front());

	auto P = P0();
	auto cond = Aft_CorrOptNode_IterativeTools::template
		Correct<Aft2d_EdgeSurface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform, Aft_SizeCorr_IterativeInfo>
		(
			*MetricMap(),
			P,
			*Front(), theInfo
			);
	if (cond AND NOT theInfo.IgnoreNonConvergency())
	{
		FatalErrorIn(FunctionSIG)
			<< " failed to calculate optimized node" << endl
			<< abort(FatalError);
	}

	if (verbose AND cond)
	{
		Info << " WARNING: failed to calculate optimized node." << endl;
	}

	CoordRef() = std::move(P);
	Change_IsDone() = Standard_True;
}