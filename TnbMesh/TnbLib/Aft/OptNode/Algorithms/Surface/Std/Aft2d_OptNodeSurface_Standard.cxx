#include <Aft2d_OptNodeSurface_Standard.hxx>

#include <Aft2d_IterOptNodeSurface_Calculator.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft2d_CorrOptNodeSurface_Iterative.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <MeshBase_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_OptNodeSurface_Standard::Perform()
{
	Debug_Null_Pointer(this->GetInfo());

	auto alg = std::make_shared<Aft2d_IterOptNodeSurface_Calculator>(GetInfo());
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