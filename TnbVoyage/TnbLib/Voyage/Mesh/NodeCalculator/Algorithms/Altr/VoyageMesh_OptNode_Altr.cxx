#include <VoyageMesh_OptNode_Altr.hxx>

#include <VoyageMesh_IterOptNode_Calculator.hxx>
#include <VoyageMesh_CorrOptNode_Iterative.hxx>
#include <VoyageMesh_AltrOptNode.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::VoyageMesh_OptNode_Altr::Perform()
{
	Debug_Null_Pointer(this->GetInfo());
	Debug_Null_Pointer(this->Front());
	Debug_Null_Pointer(this->MetricMap());
	const auto size = this->MetricMap()->CalcElementSize(this->Front()->Centre());
	auto uni_sizefun = 
		std::make_shared<GeoSizeFun2d_Uniform>
		(size, this->MetricMap()->BoundingBox());
	// Create a new metric map based on the uniform size function. [9/12/2023 Payvand]
	auto metric_procsr = 
		std::make_shared<VoyageMesh_MetricPrcsr>
		(uni_sizefun, this->MetricMap()->MetricFunction(), this->MetricMap()->Info());
	auto alg = std::make_shared<VoyageMesh_IterOptNode_Calculator>(this->GetInfo());
	Debug_Null_Pointer(alg);

	alg->SetFront(this->Front());
	alg->SetMetricMap(metric_procsr);
	alg->SetSize(this->Size());

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	if (NOT alg->IsConverged())
	{
		AlterAlg()->SetFront(this->Front());
		AlterAlg()->SetMetricMap(metric_procsr);
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