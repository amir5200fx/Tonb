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
	auto P = theP0;

	const auto& map = theMap;
	const auto& info = theInfo;

	const auto& edge = theEdge;

	const auto& domain = map.BoundingBox();
	if (NOT domain.IsInside(P))
	{
		P = MeshBase_Tools::CorrectCoord(edge.Centre(), P, domain);
	}

	const auto omega = info.UnderRelaxation();
	const auto tol = info.Tolerance();

	Debug_Null_Pointer(edge.Node0());
	Debug_Null_Pointer(edge.Node1());
	const auto& v0 = edge.Node0()->Coord();
	const auto& v1 = edge.Node1()->Coord();

	Standard_Boolean cond = Standard_True;
	Standard_Integer Iter = 0;
	do
	{
		auto d0 = map.CalcUnitDistance(v0, P);
		auto d1 = map.CalcUnitDistance(v1, P);
		//std::cout << "iter: " << Iter << std::endl;
		//std::cout << " v0: " << v0 << ", v1: " << v1 << std::endl;
		//std::cout << "d0: " << d0 << ", d1: " << d1 << std::endl;
		Debug_If_Condition(d0 <= gp::Resolution());
		Debug_If_Condition(d1 <= gp::Resolution());

		auto Pa = v0 + (P - v0) / d0;
		auto Pb = v1 + (P - v1) / d1;

		auto Pn = 0.5 * (Pa + Pb);
		auto dP = Pn - P;

		P += omega * dP;
		//std::cout << "P: " << P << std::endl;
		
		if (ABS(1.0 - d0) <= tol AND ABS(1.0 - d1) <= tol)
		{
			cond = Standard_False;
			break;
		}

		if (NOT domain.IsInside(P))
		{
			//std::cout << "corrected!" << std::endl;
			P = MeshBase_Tools::CorrectCoord(edge.Centre(), P, domain);
		}
	} while (++Iter <= info.MaxNbIters());
	//std::cout << std::endl;
	if (NOT domain.IsInside(P))
	{
		P = MeshBase_Tools::CorrectCoord(edge.Centre(), P, domain);
	}

	theP0 = std::move(P);
	return cond;
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

		P += omega * dp;

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