#include <VoyageMesh_AltrOptNode_NelderMead.hxx>

#include <VoyageMesh_AltrOptNode_NelderMeadObj.hxx>
#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>
#include <NumAlg_NelderMead.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageMesh_AltrOptNode_NelderMead::Perform()
{
	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	NumAlg_NelderMead<VoyageMesh_AltrOptNode_NelderMeadObj> alg;
	
	alg.SetP0(Front()->Node0()->Coord());
	alg.SetP1(Front()->Node1()->Coord());
	alg.SetP2(P0());

	alg.SetInfo(AlgInfo());
	alg.SetMetricMap(MetricMap());
	alg.SetTolerance(AlgInfo()->Tolerance());

	alg.Perform();

	CorrectedRef() = alg.BestVertex();

	Change_IsDone() = Standard_True;
}