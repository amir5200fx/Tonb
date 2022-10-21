#include <Aft2d_OptNodeSurfaceUniMetric_Standard.hxx>

#include <Aft2d_StdOptNodeSurfaceUniMetric_Calculator.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <MeshBase_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_OptNodeSurfaceUniMetric_Standard::Perform()
{
	auto alg = std::make_shared<Aft2d_StdOptNodeSurfaceUniMetric_Calculator>();
	Debug_Null_Pointer(alg);

	alg->SetFront(Front());
	alg->SetMetricMap(MetricMap());
	alg->SetSize(Size());

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	if (NOT MetricMap()->BoundingBox().IsInside(alg->Coord()))
	{
		ChangeCoord() = MeshBase_Tools::CorrectCoord(Front()->Centre(), alg->Coord(), MetricMap()->BoundingBox());
	}
	else
	{
		ChangeCoord() = alg->Coord();
	}
	Change_IsDone() = Standard_True;
}