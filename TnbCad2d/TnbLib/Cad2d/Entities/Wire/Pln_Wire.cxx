#include <Pln_Wire.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::Pln_Wire::CalcBoundingBox
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	const auto& edges = theEdges;

	if (edges.empty())
	{
		FatalErrorIn("void tnbLib::Plane_Wire::CalcBoundingBox()")
			<< "Empty List"
			<< abort(FatalError);
	}

	auto iter = edges.begin();
	Debug_Null_Pointer(*iter);
	Debug_Null_Pointer((*iter)->Curve());

	auto box = (*iter)->Curve()->CalcBoundingBox();
	while (iter NOT_EQUAL edges.end())
	{
		const auto& x = (*iter)->Curve();

		Debug_Null_Pointer(x);
		box = Entity2d_Box::Union(box, x->CalcBoundingBox());
		iter++;
	}
	theBoundingBox_ = std::make_shared<Entity2d_Box>(box);
}

void tnbLib::Pln_Wire::CheckWire
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	const auto& edges = theEdges;

	if (edges.size() IS_EQUAL 1)
	{
		if (NOT edges[0]->IsRing())
		{
			FatalErrorIn("void CheckWire(const edgeList& theEdges)")
				<< "Invalid Wire: the edge is not a ring" << endl
				<< abort(FatalError);
		}
		return;
	}

	forThose(Index, 1, edges.size() - 1)
	{
		const auto& edge0 = edges[Index - 1];
		const auto& edge1 = edges[Index];

		if (edge0->Vtx1() NOT_EQUAL edge1->Vtx0())
		{
			FatalErrorIn("void CheckWire(const edgeList& theEdges)")
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}
	}

	const auto& last = edges[edges.size() - 1];
	const auto& first = edges[0];

	if (last->Vtx1() NOT_EQUAL first->Vtx0())
	{
		FatalErrorIn("void CheckWire(const edgeList& theEdges)")
			<< "Invalid Wire: the wire is not closed" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Pln_Wire::CreateWire
(
	const std::shared_ptr<Pln_CmpEdge>& theEdge
)
{
	if (NOT theEdge)
	{
		FatalErrorIn("void CreateWire(const std::shared_ptr<edgeList>& theEdges)")
			<< "Null edge list!" << endl
			<< abort(FatalError);
	}

	CheckWire(theEdge->Edges());

	CalcBoundingBox(theEdge->Edges());

	theEdges_ = theEdge;

	theOrientation_ = Pln_Tools::RetrieveOrientation(*this);
}

tnbLib::Pln_Wire::Pln_Wire
(
	const std::shared_ptr<Pln_CmpEdge>& theEdge
)
{
	CreateWire(theEdge);
}

tnbLib::Pln_Wire::Pln_Wire
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Pln_CmpEdge>& theEdge
)
	: Pln_Entity(theIndex)
{
	CreateWire(theEdge);
}

tnbLib::Pln_Wire::Pln_Wire
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Pln_CmpEdge>& theEdge
)
	: Pln_Entity(theIndex, theName)
{
	CreateWire(theEdge);
}

Standard_Integer 
tnbLib::Pln_Wire::NbEdges() const
{
	Debug_Null_Pointer(theEdges_);
	return theEdges_->NbEdges();
}

std::tuple<Standard_Real, Standard_Real> 
tnbLib::Pln_Wire::BoundTolerance() const
{
	auto vertices = RetrieveVertices();
	auto minTol = RealLast();
	auto maxTol = RealFirst();

	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);

		if (minTol > x->Precision())
			minTol = x->Precision();

		if (maxTol < x->Precision())
			maxTol = x->Precision();
	}
	auto t = std::make_tuple(minTol, maxTol);
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Pln_Wire::Polygon() const
{
	auto poly = std::make_shared<Entity2d_Polygon>();
	Debug_Null_Pointer(poly);

	auto& pts = poly->Points();
	for (const auto& x : Edges())
	{
		if (NOT x->Mesh())
		{
			FatalErrorIn("std::shared_ptr<tnbLib::Entity2d_Polygon> Pln_Wire::Polygon() const")
				<< "the edge doesn't has any mesh on itself!" << endl
				<< abort(FatalError);
		}

		const auto& points = x->Mesh()->Points();
		for (auto i = 0; i < points.size() - 1; i++)
		{
			pts.push_back(points[i]);
		}
	}

	if (pts.size())
	{
		pts.push_back(pts[0]);
	}

	return std::move(poly);
}

const std::vector<std::shared_ptr<tnbLib::Pln_Edge>>& 
tnbLib::Pln_Wire::Edges() const
{
	return theEdges_->Edges();
}

std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> 
tnbLib::Pln_Wire::RetrieveVertices() const
{
	std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> vertices;
	RetrieveVerticesTo(vertices);

	return std::move(vertices);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Pln_Wire::RetrieveCurves() const
{
	std::vector<std::shared_ptr<tnbLib::Pln_Curve>> curves;
	RetrieveCurvesTo(curves);

	return std::move(curves);
}

//std::shared_ptr<tnbLib::Pln_Wire>
//tnbLib::Pln_Wire::Copy() const
//{
//	const auto& cmpEdge = CmpEdge();
//	
//	auto vertices = RetrieveVertices();
//
//	std::vector<std::shared_ptr<Pln_Vertex>> copy_vertices;
//	copy_vertices.reserve(vertices.size());
//
//	for (const auto& x : vertices)
//	{
//		Debug_Null_Pointer(x);
//		copy_vertices.push_back(x->Copy());
//	}
//
//
//}

void tnbLib::Pln_Wire::ApplyOrientation
(
	const Pln_Orientation theOrient
)
{
	if (theOrient IS_EQUAL Pln_Orientation::Pln_Orientation_Unknown)
	{
		FatalErrorIn("void tnbLib::Pln_Wire::ApplyOrientation()")
			<< "Invalid orientation set" << endl
			<< abort(FatalError);
	}

	if (theOrient IS_EQUAL Orientation())
	{
		return;
	}

	Reverse();
}

void tnbLib::Pln_Wire::Reverse()
{
	if (Orientation() IS_EQUAL Pln_Orientation_Unknown)
	{
		FatalErrorIn("void tnbLib::Plane_Wire::Reverse()")
			<< "Unknown orientation"
			<< abort(FatalError);
	}

	theEdges_->Reverse();
	theOrientation_ = tnbLib::Reverse(Orientation());
}

void tnbLib::Pln_Wire::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
) const
{
	theVertices.reserve(NbEdges());
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		theVertices.push_back(x->Vtx0());
	}
}

void tnbLib::Pln_Wire::RetrieveCurvesTo
(
	std::vector<std::shared_ptr<Pln_Curve>>& theCurves
) const
{
	const auto& edges = Edges();

	theCurves.reserve(edges.size());
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		theCurves.push_back(x->Curve());
	}
}

void tnbLib::Pln_Wire::Approx
(
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
) const
{
	const auto& edges = Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Approx(theInfo);
	}
}