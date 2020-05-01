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

tnbLib::Entity2d_Box
tnbLib::Pln_Wire::CalcBoundingBox
(
	const Standard_Real theTol
) const
{
	const auto& edges = Edges();

	if (edges.empty())
	{
		FatalErrorIn("void tnbLib::Plane_Wire::CalcBoundingBox()")
			<< "Empty List"
			<< abort(FatalError);
	}

	auto iter = edges.begin();
	Debug_Null_Pointer(*iter);
	Debug_Null_Pointer((*iter)->Curve());

	Entity2d_Box box = (*iter)->Curve()->BoundingBox(0);
	while (iter NOT_EQUAL edges.end())
	{
		const auto& x = (*iter)->Curve();

		Debug_Null_Pointer(x);
		box = Entity2d_Box::Union(box, x->BoundingBox(0));
		iter++;
	}

	if (theTol > 0)
	{
		box.Expand(theTol);
	}

	return std::move(box);
}

void tnbLib::Pln_Wire::SetEdges
(
	const std::shared_ptr<Pln_CmpEdge>&& theEdges
)
{
	theEdges_ = std::move(theEdges);
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

	theEdges_ = theEdge;

	SetOrientation(Pln_Tools::RetrieveOrientation(*this));

	auto b = CalcBoundingBox(0);
	SetBoundingBox(std::move(b));
}

void tnbLib::Pln_Wire::CreateWire
(
	const std::shared_ptr<Pln_CmpEdge>&& theEdge
)
{
	if (NOT theEdge)
	{
		FatalErrorIn("void CreateWire(const std::shared_ptr<edgeList>& theEdges)")
			<< "Null edge list!" << endl
			<< abort(FatalError);
	}

	CheckWire(theEdge->Edges());

	SetEdges(std::move(theEdge));

	SetOrientation(Pln_Tools::RetrieveOrientation(*this));

	auto b = CalcBoundingBox(0);
	SetBoundingBox(std::move(b));
}

void tnbLib::Pln_Wire::CheckWireConsistency
(
	const char* theName
) const
{
	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	RetrieveVerticesTo(vertices);

	if (vertices.size() NOT_EQUAL NbEdges())
	{
		FatalErrorIn(theName)
			<< "contradictory data: the wire is not close, apparently!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Pln_Wire::ForcedTransform
(
	const gp_Trsf2d & t
)
{
	const auto& cmpEdge = CmpEdge();
	Debug_Null_Pointer(cmpEdge);

	cmpEdge->Transform(t);
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
	const std::shared_ptr<Pln_CmpEdge>&& theEdge
)
{
	CreateWire(std::move(theEdge));
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
	const std::shared_ptr<Pln_CmpEdge>&& theEdge
)
	: Pln_Entity(theIndex)
{
	CreateWire(std::move(theEdge));
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

tnbLib::Pln_Wire::Pln_Wire
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Pln_CmpEdge>&& theEdge
)
	: Pln_Entity(theIndex, theName)
{
	CreateWire(std::move(theEdge));
}

Standard_Integer 
tnbLib::Pln_Wire::NbEdges() const
{
	Debug_Null_Pointer(theEdges_);
	return theEdges_->NbEdges();
}

Standard_Integer
tnbLib::Pln_Wire::NbEntities
(
	const Pln_EntityType t
) const
{
#ifdef FULLDEBUG
	CheckWireConsistency("Standard_Integer NbEntities(const Pln_EntityType t) const");
#endif // FULLDEBUG

	if (t IS_EQUAL Pln_EntityType::VERTEX)
		return NbEdges();
	if (t IS_EQUAL Pln_EntityType::EDGE)
		return NbEdges();
	if (t IS_EQUAL Pln_EntityType::WIRE)
		return 1;
	return 0;
}

Standard_Boolean 
tnbLib::Pln_Wire::IsOrphan() const
{
	return NOT Plane().lock();
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

tnbLib::Entity2d_Box 
tnbLib::Pln_Wire::BoundingBox
(
	const Standard_Real Tol
) const
{
	auto b = Pln_WireAux::BoundingBox();
	if (Tol > 0)
	{
		b.Expand(Tol);
	}
	return std::move(b);
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

		if (x->Sense())
		{
			const auto& points = x->Mesh()->Points();
			for (auto i = 0; i < points.size() - 1; i++)
			{
				pts.push_back(points[i]);
			}
		}
		else
		{
			const auto& points = x->Mesh()->Points();
			for (auto i = points.size() - 1; i > 0; i--)
			{
				pts.push_back(points[i]);
			}
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
	Debug_Null_Pointer(theEdges_);
	return theEdges_->Edges();
}

const std::shared_ptr<tnbLib::Pln_CmpEdge>& 
tnbLib::Pln_Wire::CmpEdge() const
{
	return theEdges_;
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

std::shared_ptr<tnbLib::Pln_Entity> 
tnbLib::Pln_Wire::Copy() const
{
	auto wire = 
		std::make_shared<Pln_Wire>
		(
			Index(), Name(), 
			std::dynamic_pointer_cast<Pln_CmpEdge>(CmpEdge()->Copy()));
	Debug_Null_Pointer(wire);

	for (const auto& x : wire->Edges())
	{
		Debug_Null_Pointer(x);
		x->SetWire(wire);
	}
	return std::move(wire);
}

tnbLib::Pln_EntityType 
tnbLib::Pln_Wire::Type() const
{
	return Pln_EntityType::WIRE;
}

void tnbLib::Pln_Wire::Transform
(
	const gp_Trsf2d & t
)
{
	if (NOT IsOrphan())
	{
		FatalErrorIn("void Transform(const gp_Trsf2d& t)")
			<< " for transforming, the object must be orphan!" << endl
			<< abort(FatalError);
	}

	const auto& cmpEdge = CmpEdge();
	Debug_Null_Pointer(cmpEdge);

	cmpEdge->Transform(t);

	/*recalculating of the bounding box of the wire*/
	auto b = CalcBoundingBox(0);
	SetBoundingBox(std::move(b));
}

void tnbLib::Pln_Wire::RetrieveEntitiesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities, 
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
	{
		RetrieveVerticesTo(theEntities);
	}

	if (t IS_EQUAL Pln_EntityType::EDGE)
	{
		RetrieveEdgesTo(theEntities);
	}

	if (t IS_EQUAL Pln_EntityType::WIRE)
	{
		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
	}
}

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
	if (Orientation() IS_EQUAL Pln_Orientation::Pln_Orientation_Unknown)
	{
		FatalErrorIn("void tnbLib::Plane_Wire::Reverse()")
			<< "Unknown orientation"
			<< abort(FatalError);
	}

	theEdges_->Reverse();
	SetOrientation(tnbLib::Reverse(Orientation()));
}

void tnbLib::Pln_Wire::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
) const
{
#ifdef FULLDEBUG
	CheckWireConsistency("void Pln_Wire::RetrieveVerticesTo(Args...) const");
#endif // FULLDEBUG

	theVertices.reserve(NbEdges());
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		theVertices.push_back(x->Vtx0());
	}
}

void tnbLib::Pln_Wire::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theVertices
) const
{
#ifdef FULLDEBUG
	CheckWireConsistency("void Pln_Wire::RetrieveVerticesTo(Args...) const");
#endif // FULLDEBUG

	theVertices.reserve(NbEdges());
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		theVertices.push_back(x->Vtx0());
	}
}

void tnbLib::Pln_Wire::RetrieveEdgesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEdges
) const
{
	theEdges.reserve(NbEdges());
	const auto& edges = Edges();
	for (const auto& x : edges)
	{
		theEdges.push_back(x);
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