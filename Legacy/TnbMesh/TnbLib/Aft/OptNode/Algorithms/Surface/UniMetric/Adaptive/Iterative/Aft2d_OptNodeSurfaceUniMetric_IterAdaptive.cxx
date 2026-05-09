#include <Aft2d_OptNodeSurfaceUniMetric_IterAdaptive.hxx>

#include <Aft2d_IterOptNodeSurfaceUniMetric_Calculator.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft2d_CorrOptNodeSurfaceUniMetric_Iterative.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_OptNodeSurfaceUniMetric_IterAdaptive::Perform()
{
	Debug_Null_Pointer(this->GetInfo());

	auto alg = std::make_shared<Aft2d_IterOptNodeSurfaceUniMetric_Calculator>(GetInfo());
	Debug_Null_Pointer(alg);

	alg->SetFront(Front());
	alg->SetMetricMap(MetricMap());
	alg->SetSize(Size());

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	ChangeCoord() = alg->Coord();
	Change_IsDone() = Standard_True;
}