#include <Aft_Tools.hxx>

#include <Aft2d_Node.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_Edge.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
//#include <Aft2d_gPlnCurveSurface.hxx>
//#include <Aft2d_tPlnCurveSurface.hxx>
//#include <Aft2d_gSegmentEdge.hxx>
//#include <Aft2d_tSegmentEdge.hxx>

std::vector<std::shared_ptr<tnbLib::Aft2d_Edge>> 
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theSegments)
{
	auto segments = Aft2d_SegmentEdge::UpCast(theSegments);
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_EdgeAnIso>>
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>& theSegments)
{
	auto segments = Aft2d_SegmentEdgeAnIso::UpCast(theSegments);
	return std::move(segments);
}

//std::vector<std::shared_ptr<tnbLib::Aft2d_Edge>>
//tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>& theSegments)
//{
//	auto segments = Aft2d_gSegmentEdge::UpCast(theSegments);
//	return std::move(segments);
//}

std::vector<std::shared_ptr<tnbLib::Aft2d_Node>> 
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft2d_Edge>>& theEdges
)
{
	auto nodes = Aft2d_Edge::RetrieveNodes(theEdges);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_NodeAnIso>>
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theEdges
)
{
	auto nodes = Aft2d_EdgeAnIso::RetrieveNodes(theEdges);
	return std::move(nodes);
}

//std::vector<std::shared_ptr<tnbLib::Aft2d_NodeSurface>>
//tnbLib::Aft_Tools::RetrieveNodes
//(
//	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
//)
//{
//	auto nodes = Aft2d_EdgeSurface::RetrieveNodes(theEdges);
//	return std::move(nodes);
//}

std::vector<tnbLib::Pnt2d> 
tnbLib::Aft_Tools::RetrieveGeometry
(
	const std::vector<std::shared_ptr<Aft2d_Node>>& theNodes
)
{
	auto coords = Aft2d_Node::RetrieveGeometry(theNodes);
	return std::move(coords);
}

std::vector<tnbLib::Pnt2d>
tnbLib::Aft_Tools::RetrieveGeometry
(
	const std::vector<std::shared_ptr<Aft2d_NodeAnIso>>& theNodes
)
{
	auto coords = Aft2d_NodeAnIso::RetrieveGeometry(theNodes);
	return std::move(coords);
}

//std::vector<tnbLib::Pnt2d>
//tnbLib::Aft_Tools::RetrieveGeometry
//(
//	const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theNodes
//)
//{
//	auto coords = Aft2d_NodeSurface::RetrieveGeometry(theNodes);
//	return std::move(coords);
//}

std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>> 
tnbLib::Aft_Tools::RetrieveTopoMesh
(
	const std::shared_ptr<Aft2d_PlnCurve>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsr>& thePrcsr, 
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
)
{
	auto segments = Aft2d_PlnCurve::TopoMesh<Aft2d_SegmentEdge>(theCurve, thePrcsr, theInfo);
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdgeAnIso>>
tnbLib::Aft_Tools::RetrieveTopoMesh
(
	const std::shared_ptr<Aft2d_PlnCurveAnIso>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
)
{
	auto segments = Aft2d_PlnCurveAnIso::TopoMesh<Aft2d_SegmentEdgeAnIso>(theCurve, thePrcsr, theInfo);
	return std::move(segments);
}

void tnbLib::Aft_Tools::MergeDangles
(
	const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theWire,
	const Standard_Real tol
)
{
	Aft2d_SegmentEdge::MergeDangles(theWire, tol);
}

void tnbLib::Aft_Tools::MergeDangles
(
	const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>& theWire,
	const Standard_Real tol
)
{
	Aft2d_SegmentEdgeAnIso::MergeDangles(theWire, tol);
}

void tnbLib::Aft_Tools::ActiveBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theEdges)
{
	Aft2d_SegmentEdge::ActiveBoundaryEdges(UpCast(theEdges));
}

void tnbLib::Aft_Tools::ActiveBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>& theEdges)
{
	Aft2d_SegmentEdgeAnIso::ActiveBoundaryEdges(UpCast(theEdges));
}
