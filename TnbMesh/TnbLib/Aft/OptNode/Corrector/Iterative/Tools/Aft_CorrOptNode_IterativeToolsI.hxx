#pragma once
#include <Geo_MetricPrcsr.hxx>
#include <MeshBase_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>
template<class FrontType, class SizeFun, class MetricFun, class InfoType>
inline Standard_Boolean tnbLib::Aft_CorrOptNode_IterativeTools::Correct
(
	const Geo_MetricPrcsr<SizeFun, MetricFun>& theMap,
	typename point_type_from_sizeMap<SizeFun>::ptType & theP0,
	const FrontType & theEdge, 
	const InfoType & theInfo
)
{
	const auto& edge = theEdge;
	Debug_Null_Pointer(edge.Node0());
	Debug_Null_Pointer(edge.Node1());

	return CorrectOptNode
	(
		theMap,
		edge.Node0()->Coord(),
		edge.Node1()->Coord(),
		edge.Centre(), theP0, 1.0, theInfo
	);
}

template<class SizeFun, class MetricFun, class InfoType>
inline Standard_Boolean 
tnbLib::Aft_CorrOptNode_IterativeTools::Correct
(
	const Geo_MetricPrcsr<SizeFun, MetricFun>& theMap,
	const typename point_type_from_sizeMap<SizeFun>::ptType & theP0,
	typename point_type_from_sizeMap<SizeFun>::ptType & theP, 
	const Standard_Real h,
	const InfoType & theInfo
)
{
	auto P = theP;

	const auto& map = theMap;
	const auto& info = theInfo;

	const auto& domain = map.BoundingBox();
	if (NOT domain.IsInside(P))
	{
		P = MeshBase_Tools::CorrectCoord(theP0, P, domain);
	}

	const auto omega = info.UnderRelaxation();
	const auto tol = info.Tolerance();

	Standard_Boolean cond = Standard_True;
	Standard_Integer Iter = 0;
	do 
	{
		auto dis = map.CalcUnitDistance(theP0, P) / h;
		Debug_If_Condition(dis <= gp::Resolution());

		auto pt = theP0 + (P - theP0) / dis;
		auto dp = pt - P;

		P += /*omega **/ dp;

		if (std::abs(1.0 - dis) <= tol)
		{
			cond = Standard_False;
			break;
		}

		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theP0, P, domain);
		}
	} while (++Iter <= info.MaxNbIters());

	if (NOT domain.IsInside(P))
	{
		P = MeshBase_Tools::CorrectCoord(theP0, P, domain);
	}

	theP = std::move(P);
	return cond;
}

template<class SizeFun, class MetricFun, class InfoType>
inline Standard_Boolean
tnbLib::Aft_CorrOptNode_IterativeTools::CorrectOptNode
(
	const Geo_MetricPrcsr<SizeFun, MetricFun>& theMap,
	const Pnt2d & theV0,
	const Pnt2d & theV1,
	const Pnt2d& theCentre,
	Pnt2d & theP0,
	const Standard_Real h,
	const InfoType & theInfo
)
{
	auto P = theP0;

	const auto& map = theMap;
	const auto& info = theInfo;

	const auto& domain = map.BoundingBox();
	if (NOT domain.IsInside(P))
	{
		P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
	}

	const auto omega = info.UnderRelaxation();
	const auto tol = info.Tolerance();

	Standard_Boolean cond = Standard_True;
	Standard_Integer Iter = 0;

	Debug_If_Condition(h <= gp::Resolution());
	const auto invH = 1.0 / h;
	Standard_Real d0, d1;
	do
	{
		//std::cout << "do..." << std::endl;
		d0 = map.CalcUnitDistance(theV0, P)*invH;
		d1 = map.CalcUnitDistance(theV1, P)*invH;
		Debug_If_Condition(d0 <= gp::Resolution());
		Debug_If_Condition(d1 <= gp::Resolution());
		//std::cout << "d0: " << d0 << ", d1: " << d1 << std::endl;
		auto Pa = theV0 + (P - theV0) / d0;
		auto Pb = theV1 + (P - theV1) / d1;

		auto Pn = 0.5 * (Pa + Pb);

		auto dP = Pn - P;

		P += omega * dP;

		if (ABS(1.0 - d0) <= tol AND ABS(1.0 - d1) <= tol)
		{
			cond = Standard_False;
			break;
		}

		if (NOT domain.IsInside(P))
		{
			P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
		}
	} while (++Iter <= info.MaxNbIters());

	if (NOT domain.IsInside(P))
	{
		P = MeshBase_Tools::CorrectCoord(theCentre, P, domain);
	}

	theP0 = std::move(P);
	return cond;
}