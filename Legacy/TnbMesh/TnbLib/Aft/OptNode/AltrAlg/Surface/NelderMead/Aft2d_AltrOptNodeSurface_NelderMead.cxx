#include <Aft2d_AltrOptNodeSurface_NelderMead.hxx>

#include <Aft2d_OptNodeSurface_NelderMeadObj.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <NumAlg_NelderMead.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Aft2d_AltrOptNodeSurface_NelderMead::Perform()
{
	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	NumAlg_NelderMead<Aft2d_OptNodeSurface_NelderMeadObj> alg;

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