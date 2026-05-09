#include <VoyageMesh_OptNode_Standard.hxx>

#include <VoyageMesh_IterOptNode_Calculator.hxx>
#include <VoyageMesh_CorrOptNode_Iterative.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <MeshBase_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::VoyageMesh_OptNode_Standard::Perform()
{
	Debug_Null_Pointer(this->GetInfo());

	auto alg = std::make_shared<VoyageMesh_IterOptNode_Calculator>(GetInfo());
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