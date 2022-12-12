#include <Aft_Tools.hxx>

#include <Aft2d_Edge.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_SegmentEdgeUniMetric.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
#include <Aft_Elements.hxx>
#include <Aft_Nodes.hxx>
#include <Entity2d_Chain.hxx>
//#include <Aft2d_gPlnCurveSurface.hxx>
//#include <Aft2d_tPlnCurveSurface.hxx>
#include <Aft2d_gSegmentEdge.hxx>
#include <Aft2d_tSegmentEdge.hxx>
#include <Aft2d_gSegmentEdgeUniMetric.hxx>
#include <Aft2d_tSegmentEdgeUniMetric.hxx>

#include <Geom_Surface.hxx>

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

std::vector<std::shared_ptr<tnbLib::Aft2d_EdgeAnIso>>
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>& theSegments)
{
	auto segments = Aft2d_SegmentEdgeUniMetric::UpCast(theSegments);
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_EdgeSurface>>
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>& theSegments)
{
	auto segments = Aft2d_gSegmentEdge::UpCast(theSegments);
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_EdgeSurface>>
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>& theSegments)
{
	auto segments = Aft2d_tSegmentEdge::UpCast(theSegments);
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_EdgeSurface>>
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>& theSegments)
{
	auto segments = Aft2d_gSegmentEdgeUniMetric::UpCast(theSegments);
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_EdgeSurface>>
tnbLib::Aft_Tools::UpCast(const std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>& theSegments)
{
	auto segments = Aft2d_tSegmentEdgeUniMetric::UpCast(theSegments);
	return std::move(segments);
}

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

std::vector<std::shared_ptr<tnbLib::Aft2d_NodeSurface>>
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
)
{
	auto nodes = Aft2d_EdgeSurface::RetrieveNodes(theEdges);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_Node>>
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft2d_Element>>& theElements
)
{
	auto nodes = Aft2d_Element::RetrieveNodes(theElements);
	return std::move(std::move(nodes));
}

std::vector<std::shared_ptr<tnbLib::Aft2d_NodeAnIso>>
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft2d_ElementAnIso>>& theElements
)
{
	auto nodes = Aft2d_ElementAnIso::RetrieveNodes(theElements);
	return std::move(std::move(nodes));
}

std::vector<std::shared_ptr<tnbLib::Aft2d_NodeSurface>>
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
)
{
	auto nodes = Aft2d_ElementSurface::RetrieveNodes(theElements);
	return std::move(std::move(nodes));
}

std::vector<std::shared_ptr<tnbLib::Aft3d_Node>>
tnbLib::Aft_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft3d_Element>>& theElements
)
{
	auto nodes = Aft3d_Element::RetrieveNodes(theElements);
	return std::move(std::move(nodes));
}

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

std::vector<tnbLib::Pnt2d>
tnbLib::Aft_Tools::RetrieveGeometry
(
	const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theNodes
)
{
	auto coords = Aft2d_NodeSurface::RetrieveGeometry(theNodes);
	return std::move(coords);
}
template<>
std::vector<tnbLib::connectivity::triple> 
tnbLib::Aft_Tools::RetrieveTriangleConnectivities
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theElements
)
{
	std::vector<connectivity::triple> indices;
	indices.reserve(theElements.size());
	for (const auto& x : theElements)
	{
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto i0 = n0->Index();
		auto i1 = n1->Index();

		connectivity::triple v;
		v.Value(0) = i0;
		v.Value(1) = i1;
		v.Value(2) = i0;

		indices.push_back(std::move(v));
	}
	return std::move(indices);
}

template<>
std::vector<tnbLib::connectivity::triple>
tnbLib::Aft_Tools::RetrieveTriangleConnectivities
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theElements,
	const std::map<Standard_Integer, Standard_Integer>& theIndices
)
{
	std::vector<connectivity::triple> indices;
	indices.reserve(theElements.size());
	try
	{
		for (const auto& x : theElements)
		{
			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto i0 = n0->Index();
			auto i1 = n1->Index();

			connectivity::triple v;
			v.Value(0) = theIndices.at(i0);
			v.Value(1) = theIndices.at(i1);
			v.Value(2) = theIndices.at(i0);

			indices.push_back(std::move(v));
		}
	}
	catch (const std::out_of_range&)
	{
		FatalErrorIn(FunctionSIG)
			<< "out of rage error has been detected!" << endl
			<< abort(FatalError);
	}
	catch (const std::exception&)
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected error has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(indices);
}

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

void tnbLib::Aft_Tools::CalcCood3d
(
	const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theNodes,
	const Geom_Surface & theSurface
)
{
	for (const auto& n : theNodes)
	{
		Debug_Null_Pointer(n);
		auto[x, y] = n->Coord().Components();

		n->SetCoord3D(theSurface.Value(x, y));
	}
}

//void tnbLib::Aft_Tools::Connect(const std::vector<std::shared_ptr<Aft2d_Edge>>& theEdges)
//{
//	for (const auto& x : theEdges)
//	{
//		const auto& n0 = x->Node0();
//		const auto& n1 = x->Node1();
//
//		Debug_Null_Pointer(n0);
//		Debug_Null_Pointer(n1);
//
//		n0->InsertToEdges(x->Index(), x);
//		n1->InsertToEdges(x->Index(), x);
//	}
//}