#include <Aft2d_OptNode_nonIterAdaptive.hxx>

#include <Aft2d_OptNode_Analytical.hxx>
#include <Aft2d_CorrOptNode_Fraction.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>
#include <Aft2d_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_OptNode_nonIterAdaptive::Perform()
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

	if (NOT CorrInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no correction info has been found!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	if (Size() <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid element size has been detected" << endl
			<< abort(FatalError);
	}

	auto analyAlg = std::make_shared<Aft2d_OptNode_Analytical>(Size(), *Front());
	Debug_Null_Pointer(analyAlg);

	analyAlg->Perform();
	Debug_If_Condition_Message(NOT analyAlg->IsDone(), "the algorithm is not performed!");

	auto corrAlg =
		std::make_shared<Aft2d_CorrOptNode_Fraction>
		(
			MetricMap(), Front(),
			analyAlg->Coord(),
			Size()
			);
	Debug_Null_Pointer(corrAlg);
	corrAlg->Perform(*CorrInfo());

	Debug_If_Condition_Message(NOT corrAlg->IsDone(), "the algorithm is not performed!");

	ChangeCoord() = corrAlg->Coord();
	Change_IsDone() = Standard_True;
}