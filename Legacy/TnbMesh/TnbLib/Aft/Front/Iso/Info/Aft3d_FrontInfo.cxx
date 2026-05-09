#include <Aft3d_FrontInfo.hxx>

#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>
#include <Geo3d_MetricPrcsr.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
template<>
void tnbLib::Aft3d_FrontInfo::CalcGeometries<tnbLib::Geo3d_MetricPrcsr>
(
	const std::shared_ptr<Geo3d_MetricPrcsr>& theSizeMap,
	const std::shared_ptr<Aft3d_Facet>& theFacet
	)
{
	const auto& n0 = theFacet->Node0();
	const auto& n1 = theFacet->Node1();
	const auto& n2 = theFacet->Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	const auto& P0 = n0->Coord();
	const auto& P1 = n1->Coord();
	const auto& P2 = n2->Coord();

	theFacet->SetCentre(Geo_Tools::CalcCentre(P0, P1, P2));

	const auto& e0 = theFacet->Edge0();
	const auto& e1 = theFacet->Edge1();
	const auto& e2 = theFacet->Edge2();
	Debug_Null_Pointer(e0);
	Debug_Null_Pointer(e1);
	Debug_Null_Pointer(e2);

	theFacet->SetCharLength
	(
		std::max
		(
			e0->CharLength(), 
			std::max(e1->CharLength(), e2->CharLength())
		)
	);
}

template<>
template<>
void tnbLib::Aft3d_FrontInfo::CalcGeometries<tnbLib::Geo3d_MetricPrcsr>
(
	const std::shared_ptr<Geo3d_MetricPrcsr>& theSizeMap,
	const std::shared_ptr<Aft3d_Edge>& theEdge
	)
{
	Debug_Null_Pointer(theSizeMap);
	Debug_Null_Pointer(theEdge);

	const auto& P1 = theEdge->Node0()->Coord();
	const auto& P2 = theEdge->Node1()->Coord();

	theEdge->SetCharLength(theSizeMap->CalcDistance(P1, P2));
}