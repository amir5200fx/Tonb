#include <Aft2d_OptNodeUniMetric_Standard.hxx>

#include <Aft2d_StdOptNodeUniMetric_Calculator.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_OptNodeUniMetric_Standard::Perform()
{
	auto alg = std::make_shared<Aft2d_StdOptNodeUniMetric_Calculator>();
	Debug_Null_Pointer(alg);

	alg->SetFront(Front());
	alg->SetMetricMap(MetricMap());
	alg->SetSize(Size());

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	ChangeCoord() = alg->Coord();
	Change_IsDone() = Standard_True;
}