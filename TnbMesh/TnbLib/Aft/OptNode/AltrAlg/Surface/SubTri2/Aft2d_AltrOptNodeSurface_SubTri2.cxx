#include <Aft2d_AltrOptNodeSurface_SubTri2.hxx>

#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft_CorrOptNode_IterativeTools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Entity2d_Metric1.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Aft2d_AltrOptNodeSurface_SubTri2::Iter
(
	const Standard_Integer theLev, 
	const Pnt2d & theCentre, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
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
	if (Aft_CorrOptNode_IterativeTools::CorrectOptNode(*MetricMap(), V0, V1, theCentre, p0, h, *IterInfo()))
	{
		return Iter(theLev + 1, theCentre, V0, V1, theH);
	}
	CorrectedRef() = p0;
	return Standard_True;
}

void tnbLib::Aft2d_AltrOptNodeSurface_SubTri2::Perform()
{
}