#include <Aft2d_OptNodeSurface_nonIterAdaptive.hxx>

#include <Aft2d_IterOptNodeSurface_Calculator.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>
#include <Aft2d_OptNodeAnIso_nonIterAdaptiveInfo.hxx>
#include <Aft2d_CorrOptNodeSurface_Fraction.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_OptNodeSurface_nonIterAdaptive::Perform()
{
	Debug_Null_Pointer(this->GetInfo());
	Debug_Null_Pointer(GetInfo()->CalculatorInfo());
	Debug_Null_Pointer(GetInfo()->CorrectorInfo());

	auto alg = std::make_shared<Aft2d_IterOptNodeSurface_Calculator>(GetInfo()->CalculatorInfo());
	Debug_Null_Pointer(alg);

	alg->SetFront(Front());
	alg->SetMetricMap(MetricMap());
	alg->SetSize(Size());

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	auto corrector =
		std::make_shared<Aft2d_CorrOptNodeSurface_Fraction>
		(
			alg, MetricMap(),
			Front(), alg->Coord(),
			Size()
			);
	Debug_Null_Pointer(corrector);

	corrector->Perform(*GetInfo()->CorrectorInfo());
	Debug_If_Condition_Message(NOT corrector->IsDone(), "the algorithm is not performed!");

	ChangeCoord() = corrector->Coord();
	Change_IsDone() = Standard_True;
}