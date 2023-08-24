#include <VoyageMesh_CorrOptNode_Iterative.hxx>

#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_Node.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::VoyageMesh_CorrOptNode_Iterative::Perform
(
	const Aft_SizeCorr_IterativeInfo& theInfo
)
{
	Debug_Null_Pointer(MetricMap());
	Debug_Null_Pointer(Front());

	auto P = P0();
	auto cond = Aft_CorrOptNode_IterativeTools::template
		Correct<VoyageMesh_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction, Aft_SizeCorr_IterativeInfo>
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

	IsConverged_ = !cond;
	CoordRef() = std::move(P);
	Change_IsDone() = Standard_True;
}