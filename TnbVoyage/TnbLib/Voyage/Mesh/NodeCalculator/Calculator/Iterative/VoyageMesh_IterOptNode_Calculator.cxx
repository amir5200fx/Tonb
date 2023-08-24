#include <VoyageMesh_IterOptNode_Calculator.hxx>

#include <VoyageMesh_OptNode_Analytical.hxx>
#include <VoyageMesh_CorrOptNode_Iterative.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <VoyageMesh_Edge.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageMesh_IterOptNode_Calculator::Perform()
{
#ifdef _DEBUG
	if (NOT Front())
	{
		FatalErrorIn(FunctionSIG)
			<< "no front entity has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT MetricMap())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric map has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT MetricMap()->MetricFunction())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric function has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT IterInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no iteration info has been found." << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	if (Size() <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid element size has been detected" << endl
			<< abort(FatalError);
	}

	auto m = MetricMap()->CalcMetric(Front()->Centre());

	const auto& v0 = Front()->Node0()->Coord();
	const auto& v1 = Front()->Node1()->Coord();
	const auto len = MetricMap()->CalcUnitDistance(v0, v1) / 2.0;

	VoyageMesh_OptNode_Analytical alg(Size(), len, m, *Front());
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

	auto corrector =
		std::make_shared<VoyageMesh_CorrOptNode_Iterative>
		(
			MetricMap(),
			Front(),
			alg.Coord(), Size()
		);
	Debug_Null_Pointer(corrector);

	corrector->Perform(*IterInfo());
	Debug_If_Condition_Message(NOT corrector->IsDone(), "the algorithm is not performed!");

	ChangeCoord() = corrector->Coord();
	Change_IsConverged() = corrector->IsConverged();

	Change_IsDone() = Standard_True;
}