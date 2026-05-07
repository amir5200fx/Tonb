#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>

#include <Aft2d_OptNodeSurface_NelderMeadObj.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Entity2d_Metric1.hxx>
#include <NumAlg_NelderMead.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Aft2d_AltrOptNodeSurface_SubTri::DEFAULT_MAX_LEV = 3;

Standard_Boolean 
tnbLib::Aft2d_AltrOptNodeSurface_SubTri::Iter
(
	const Standard_Integer theLev,
	const Pnt2d & theCentre, 
	const Pnt2d& theP0, 
	const Pnt2d& theP1, 
	const Standard_Real theH
)
{
	if (theLev > MaxLevel())
	{
		return Standard_False;
	}

	const auto denom = std::pow(2.0, (Standard_Real)(theLev + 1));
	auto V0 = MEAN(theCentre, theP0);
	auto V1 = MEAN(theCentre, theP1);

	//const auto d0 = 1.0 / (denom*denom);
	const auto h = std::sqrt(1.0 / (denom*denom) + 0.75)*theH;
	
	auto p0 = P0();
	if (Aft_CorrOptNode_IterativeTools::CorrectOptNode(*MetricMap(), V0, V1, theCentre, p0, h, *SizeCorrInfo()))
	{
		return Iter(theLev + 1, theCentre, V0, V1, theH);
	}
	CorrectedRef() = p0;
	return Standard_True;
}

void tnbLib::Aft2d_AltrOptNodeSurface_SubTri::Perform()
{
	Debug_Null_Pointer(SizeCorrInfo());
	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	const auto& centre = Front()->Centre();
	
	const auto& node0 = Front()->Node0();
	const auto& node1 = Front()->Node1();
	Debug_Null_Pointer(node0);
	Debug_Null_Pointer(node1);

	const auto& v0 = node0->Coord();
	const auto& v1 = node1->Coord();

	CorrectedRef() = P0();

	if (Iter(1, centre, v0, v1, 1.0))
	{
		IsConvergedRef() = Standard_True;
	}
	else
	{
		NumAlg_NelderMead<Aft2d_OptNodeSurface_NelderMeadObj> alg;

		alg.SetP0(Front()->Node0()->Coord());
		alg.SetP1(Front()->Node1()->Coord());
		alg.SetP2(CorrectedRef());

		alg.SetInfo(NelderMeadInfo());
		alg.SetMetricMap(MetricMap());
		alg.SetTolerance(NelderMeadInfo()->Tolerance());

		alg.Perform();

		CorrectedRef() = alg.BestVertex();

		IsConvergedRef() = alg.IsConverged();
	}
	Change_IsDone() = Standard_True;
}