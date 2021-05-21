#include <Cad_ShapeSection.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#undef DebugInfo
#include <BRepAlgo_Section.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BOPAlgo_Builder.hxx>

tnbLib::Cad_ShapeSection::Cad_ShapeSection
(
	const gp_Pln & thePlane, 
	const TopoDS_Shape & theShape
)
	: thePlane_(thePlane)
	, theShape_(theShape)
	, Approx_(Standard_True)
	, pPlaneCurve_(Standard_False)
	, pShapeCurve_(Standard_False)
	, ParallelMode_(Standard_True)
{
	//- empty body
}

void tnbLib::Cad_ShapeSection::Perform()
{
	BRepAlgoAPI_Section alg;
	alg.Init1(thePlane_);
	alg.Init2(theShape_);
	alg.Approximation(Approx_);
	alg.ComputePCurveOn1(pPlaneCurve_);
	alg.ComputePCurveOn2(pShapeCurve_);

	alg.SetRunParallel(ParallelMode_);
	alg.Build();

	if (alg.HasErrors())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm has failed!" << endl
			<< abort(FatalError);
	}
	if (NOT alg.IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	theSection_ = alg.Shape();

	Change_IsDone() = Standard_True;
}