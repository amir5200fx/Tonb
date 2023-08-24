#include <VoyageMesh_OptNode_Altr.hxx>

#include <VoyageMesh_IterOptNode_Calculator.hxx>
#include <VoyageMesh_CorrOptNode_Iterative.hxx>
#include <VoyageMesh_AltrOptNode.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::VoyageMesh_OptNode_Altr::Perform()
{
	Debug_Null_Pointer(this->GetInfo());

	auto alg = std::make_shared<VoyageMesh_IterOptNode_Calculator>(this->GetInfo());
	Debug_Null_Pointer(alg);

	alg->SetFront(this->Front());
	alg->SetMetricMap(this->MetricMap());
	alg->SetSize(this->Size());

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	if (NOT alg->IsConverged())
	{
		AlterAlg()->SetFront(this->Front());
		AlterAlg()->SetMetricMap(this->MetricMap());
		AlterAlg()->SetElmSize(this->Size());
		AlterAlg()->SetP0(alg->Coord());

		AlterAlg()->Perform();
		Debug_If_Condition_Message(NOT AlterAlg()->IsDone(), "the application is not performed!");

		//std::cout << "is converged? " << AlterAlg()->IsConverged() << std::endl;
		ChangeCoord() = AlterAlg()->Corrected();
	}
	else
	{
		ChangeCoord() = alg->Coord();
	}
	Change_IsDone() = Standard_True;
}