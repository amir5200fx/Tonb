#include <Cad2d_Modeler_Tools.hxx>

#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_Modeler_SrchEng.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Curve.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GCE2d_MakeArcOfCircle.hxx>
#include <GCE2d_MakeArcOfEllipse.hxx>
#include <GCE2d_MakeArcOfHyperbola.hxx>
#include <GCE2d_MakeArcOfParabola.hxx>
#include <GCE2d_MakeCircle.hxx>
#include <GCE2d_MakeEllipse.hxx>

#include <algorithm>

namespace tnbLib
{

	std::shared_ptr<Pln_Edge> Make_Edge
	(
		const opencascade::handle<Geom2d_Curve>& geom,
		const Pnt2d& p0,
		const Pnt2d& p1
	)
	{
		auto v0 = std::make_shared<Pln_Vertex>(0, p0);
		Debug_Null_Pointer(v0);

		auto v1 = std::make_shared<Pln_Vertex>(1, p1);
		Debug_Null_Pointer(v1);

		auto curve = std::make_shared<Pln_Curve>(0, geom);
		Debug_Null_Pointer(curve);

		auto edge = std::make_shared<Pln_Edge>(std::move(v0), std::move(v1), std::move(curve));
		Debug_Null_Pointer(edge);

		return std::move(edge);
	}

	std::shared_ptr<Pln_Ring> Make_Ring
	(
		const opencascade::handle<Geom2d_Curve>& geom,
		const Pnt2d& theP
	)
	{
		auto v = std::make_shared<Pln_Vertex>(0, theP);
		Debug_Null_Pointer(v);

		auto curve = std::make_shared<Pln_Curve>(0, geom);
		Debug_Null_Pointer(curve);

		auto edge = std::make_shared<Pln_Ring>(v, std::move(curve));
		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeSegment maker(theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge = Make_Edge(geom, theP0, theP1);
		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Standard_Real theAngle, 
	const Standard_Real theLength
)
{
	const auto V = theLength* gp_Dir2d(cos(theAngle), sin(theAngle));
	Pnt2d P1(theP0.X() + V.X(), theP0.Y() + V.Y());

	auto edge = MakeSegment(theP0, P1);
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Pnt2d & theP2
)
{
	GCE2d_MakeArcOfCircle maker(theP0, theP1, theP2);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge = 
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()), 
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const Pnt2d & theP0, 
	const Vec2d & theV0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfCircle maker(theP0, theV0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const gp_Circ2d & theCirc, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfCircle maker(theCirc, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const gp_Circ2d & theCirc, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfCircle maker(theCirc, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeElipsArc
(
	const gp_Elips2d & theElips, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfEllipse maker(theElips, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::cad2dLib::Modeler_Tools::MakeElipsArc
(
	const gp_Elips2d & theElips,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfEllipse maker(theElips, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeHyprArc
(
	const gp_Hypr2d & theHypr,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfHyperbola maker(theHypr, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeHyprArc
(
	const gp_Hypr2d & theHypr, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfHyperbola maker(theHypr, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeParbCurve
(
	const gp_Parab2d & theParab, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfParabola maker(theParab, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeParabCurve
(
	const gp_Parab2d & theParab,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfParabola maker(theParab, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & C
)
{
	GCE2d_MakeCircle maker(C);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & C,
	const Pnt2d & theP
)
{
	GCE2d_MakeCircle maker(C, theP);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Pnt2d & theP2
)
{
	GCE2d_MakeCircle maker(theP0, theP1, theP2);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theC, 
	const Standard_Real theRadius
)
{
	GCE2d_MakeCircle maker(theC, theRadius);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theC, 
	const Pnt2d & theP
)
{
	GCE2d_MakeCircle maker(theC, theP);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::cad2dLib::Modeler_Tools::MakeEllipse
(
	const gp_Elips2d & E
)
{
	GCE2d_MakeEllipse maker(E);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::cad2dLib::Modeler_Tools::MakeEllipse
(
	const Pnt2d & theS0, 
	const Pnt2d & theS1,
	const Pnt2d & theCenter
)
{
	GCE2d_MakeEllipse maker(theS0, theS1, theCenter);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::cad2dLib::Modeler_Tools::MakeRectangular
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(4);

	auto p0 = theP0;
	auto p1 = Pnt2d(theP1.X(), theP0.Y());
	auto p2 = theP1;
	auto p3 = Pnt2d(theP0.X(), theP1.Y());

	auto e0 = MakeSegment(p0, p1);
	auto e1 = MakeSegment(p1, p2);
	auto e2 = MakeSegment(p2, p3);
	auto e3 = MakeSegment(p3, p0);

	edges.push_back(std::move(e0));
	edges.push_back(std::move(e1));
	edges.push_back(std::move(e2));
	edges.push_back(std::move(e3));

	return std::move(edges);
}

#include <Geo_SearchTree.hxx>
#include <Pln_Vertex.hxx>
#include <Cad2d_Modeler_Corner.hxx>
#include <Cad2d_Modeler_SrchEng.hxx>

Standard_Real 
tnbLib::cad2dLib::Modeler_Tools::CalcMaxTolerance
(
	const Pnt2d & theCentre,
	const std::shared_ptr<Modeler_Corner>& theCorner
)
{
	Debug_Null_Pointer(theCorner);

	auto maxTol = (Standard_Real)0;
	for (const auto& x : theCorner->Vertices())
	{
		Debug_Null_Pointer(x.second);
		const auto& vtx = x.second;

		auto dis = vtx->Coord().Distance(theCentre);
		if (dis > maxTol)
		{
			maxTol = dis;
		}
	}
	return maxTol;
}

namespace tnbLib
{

	const std::shared_ptr<cad2dLib::Modeler_Corner>&
		FindCorner
		(
			const std::shared_ptr<Pln_Vertex>& vtx,
			std::map<Standard_Integer, std::shared_ptr<cad2dLib::Modeler_Corner>>& vtxToCorners
		)
	{
		const auto id = vtx->Index();
		auto iter = vtxToCorners.find(id);
		if (iter IS_EQUAL vtxToCorners.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the tree!" << endl
				<< abort(FatalError);
		}
		return iter->second;
	}

	std::shared_ptr<Pln_Vertex>
		RemoveVtxFromCorner
		(
			const std::shared_ptr<Pln_Vertex>& vtx,
			const std::shared_ptr<cad2dLib::Modeler_Corner>& corner
		)
	{
		auto removed = corner->Remove(vtx->Index());
		return std::move(removed);
	}

	void CheckRemoved
	(
		const std::shared_ptr<Pln_Vertex>& vtx,
		const std::shared_ptr<Pln_Vertex>& removed
	)
	{
		if (vtx NOT_EQUAL removed)
		{
			FatalErrorIn(FunctionSIG)
				<< "the two vertices are not same!" << endl
				<< abort(FatalError);
		}
	}

	std::shared_ptr<Pln_Edge>
		RemoveVerticesFromCorners
		(
			const std::shared_ptr<Pln_Edge>& theEdge,
			std::map<Standard_Integer, std::shared_ptr<cad2dLib::Modeler_Corner>>& vtxToCorners
		)
	{
		const auto& v0 = theEdge->Vtx0();
		Debug_Null_Pointer(v0);

		const auto& v1 = theEdge->Vtx1();
		Debug_Null_Pointer(v1);

		const auto& crn0 = FindCorner(v0, vtxToCorners);
		const auto& crn1 = FindCorner(v1, vtxToCorners);

		CheckRemoved(v0, RemoveVtxFromCorner(v0, crn0));
		CheckRemoved(v1, RemoveVtxFromCorner(v1, crn1));

		if (crn1->NbVertices())
		{
			const auto& vertices = crn1->Vertices();
			if (vertices.size() NOT_EQUAL 1)
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			const auto& vtx = vertices.begin()->second;
			Debug_If_Condition(vtx->NbEdges() NOT_EQUAL 1);

			auto edge = vtx->Edges().begin()->second.lock();
			Debug_Null_Pointer(edge);

			return edge;
		}

		if (crn0->NbVertices())
		{
			const auto& vertices = crn0->Vertices();
			if (vertices.size() NOT_EQUAL 1)
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			const auto& vtx = vertices.begin()->second;
			Debug_If_Condition(vtx->NbEdges() NOT_EQUAL 1);

			auto edge = vtx->Edges().begin()->second.lock();
			Debug_Null_Pointer(edge);

			return edge;
		}
		return nullptr;
	}
}

namespace tnbLib
{
	namespace mergeFunLib
	{
		struct Corner
		{
			std::shared_ptr<Pln_Vertex> vtx0;
			std::shared_ptr<Pln_Vertex> vtx1;
		};

		struct Segment
		{
			std::shared_ptr<Pln_Edge> edge;

			size_t corner0;
			size_t corner1;
			
		};

		static std::tuple<std::vector<std::shared_ptr<Segment>>, std::vector<std::shared_ptr<Corner>>>
			RetrieveSegments
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const std::map<Standard_Integer, std::shared_ptr<cad2dLib::Modeler_Corner>>& theVtxToCorners
			)
		{
			std::vector<std::shared_ptr<Corner>> corners;
			corners.reserve(theEdges.size());

			std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>> paired;
			for (const auto& x : theEdges)
			{
				Debug_Null_Pointer(x);

				std::shared_ptr<Pln_Vertex> v0;

				auto piter = paired.find(x->Vtx1()->Index());
				if (piter IS_EQUAL paired.end())
				{
					v0 = x->Vtx1();
				}
				else
				{
					v0 = x->Vtx0();
				}

				auto iter = theVtxToCorners.find(v0->Index());
				if (iter IS_EQUAL theVtxToCorners.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "unable to find the item" << endl
						<< abort(FatalError);
				}
				const auto& crn = iter->second;

				const auto& vertices = crn->Vertices();
				Debug_If_Condition(vertices.size() NOT_EQUAL 2);

				auto iter1 = vertices.begin();
				std::shared_ptr<Pln_Vertex> v1;
				
				if (iter1->second NOT_EQUAL v0) v1 = iter1->second;
				else
				{
					iter1++;
					v1 = iter1->second;
				}
				Debug_If_Condition(v0 IS_EQUAL v1);

				auto insert = paired.insert(std::make_pair(v1->Index(), v1));
				Debug_If_Condition(NOT insert.second);

				auto c = std::make_shared<Corner>();
				c->vtx0 = std::move(v0);
				c->vtx1 = std::move(v1);

				corners.push_back(std::move(c));
			}

			std::vector<std::shared_ptr<Segment>> segments;
			segments.reserve(theEdges.size());

			int k = 0;
			for (const auto& x : theEdges)
			{
				Debug_Null_Pointer(x);
				auto seg = std::make_shared<Segment>();

				seg->edge = x;
				auto k0 = (k - 1) % theEdges.size();
				
				seg->corner0 = k0;
				seg->corner1 = k;

				segments.push_back(std::move(seg));

				k++;
			}
			auto t = std::make_tuple(std::move(segments), std::move(corners));
			return std::move(t);
		}

	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::cad2dLib::Modeler_Tools::MakeConsecutive
(
	const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
)
{
	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(theCorners.size());
	if (theCorners.size() IS_EQUAL 1)
	{
		const auto& crn = theCorners[0];
		if (crn->NbVertices() NOT_EQUAL 1)
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeConsecutive(const std::vector<std::shared_ptr<Modeler_Corner>>&)")
				<< "unable to create a list of consecutive edges!" << endl
				<< abort(FatalError);
		}

		std::vector<std::weak_ptr<Pln_Edge>> wEdges;
		crn->Vertices().begin()->second->RetrieveEdgesTo(wEdges);

		const auto edge = wEdges[0].lock();
		Debug_Null_Pointer(edge);

		if (NOT edge->IsRing())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeConsecutive(const std::vector<std::shared_ptr<Modeler_Corner>>&)")
				<< "unable to create a list of consecutive edges: the edge is not a ring!" << endl
				<< abort(FatalError);
		}

		edges.push_back(std::move(edge));
		return std::move(edges);
	}

	std::map<Standard_Integer, std::shared_ptr<Modeler_Corner>> vtxToCornerMap;
	std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>> indxToVerticesMap;
	for (const auto& x : theCorners)
	{
		Debug_Null_Pointer(x);

		if (x->NbVertices() NOT_EQUAL 2)
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeConsecutive(const std::vector<std::shared_ptr<Modeler_Corner>>&)")
				<< "the model is not manifold! nb. of vertices = " << x->NbVertices() << endl
				<< abort(FatalError);
		}

		const auto& vertices = x->Vertices();
		for (const auto& v : vertices)
		{
			Debug_Null_Pointer(v.second);
			auto insert = vtxToCornerMap.insert(std::make_pair(v.second->Index(), x));
			if (NOT insert.second)
			{
				FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeConsecutive(const std::vector<std::shared_ptr<Modeler_Corner>>&)")
					<< "duplicate data in vertices" << endl
					<< abort(FatalError);
			}
		}

		for (const auto& v : vertices)
		{
			Debug_Null_Pointer(v.second);
			auto insert = indxToVerticesMap.insert(std::make_pair(v.second->Index(), v.second));
			if (NOT insert.second)
			{
				FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeConsecutive(const std::vector<std::shared_ptr<Modeler_Corner>>&)")
					<< "duplicate data in vertices" << endl
					<< abort(FatalError);
			}
		}
	}

	auto current = theCorners[0];

	Debug_If_Condition(NOT current->Vertices().size());
	const auto& v0 = current->Vertices().begin()->second;

	Debug_If_Condition(NOT v0->NbEdges());
	auto edge = v0->Edges().begin()->second.lock();
	Debug_Null_Pointer(edge);

	edges.push_back(edge);
	while (edge)
	{
		edge = RemoveVerticesFromCorners(edge, vtxToCornerMap);
		if (edge)
			edges.push_back(edge);
	}

	//- return back the vertices into the corners
	for (const auto& x : vtxToCornerMap)
	{
		Debug_Null_Pointer(x.second);

		const auto& crn = x.second;
		crn->InsertToCorners(x.first, indxToVerticesMap[x.first]);
	}

	/*for (const auto& x : theCorners)
	{
		if (x->NbVertices())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeConsecutive(const std::vector<std::shared_ptr<Modeler_Corner>>&)")
				<< "the corners represent a non-manifold object or an object with multiply wires!" << endl
				<< abort(FatalError);
		}
	}*/

	const auto[segments, corners] = mergeFunLib::RetrieveSegments(edges, vtxToCornerMap);

	std::vector<std::shared_ptr<Pln_Vertex>> mVertices;
	mVertices.reserve(corners.size());

	Standard_Integer nbVrtices = 0;
	for (const auto& x : corners)
	{
		const auto& v0 = x->vtx0;
		const auto& v1 = x->vtx1;

		Debug_Null_Pointer(v0);
		Debug_Null_Pointer(v1);

		auto mPt = MEAN(v0->Coord(), v1->Coord());
		auto vtx = std::make_shared<Pln_Vertex>(++nbVrtices, mPt);
		Debug_Null_Pointer(vtx);

		mVertices.push_back(std::move(vtx));
	}

	std::vector<std::shared_ptr<Pln_Edge>> mEdges;
	mEdges.reserve(segments.size());

	Standard_Integer nbEdges = 0;
	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x);

		auto edge = std::make_shared<Pln_Edge>
			(
				mVertices[x->corner0], mVertices[x->corner1],
				x->edge->Curve(),
				x->edge->Sense());
		Debug_Null_Pointer(edge);

		edge->SetIndex(++nbEdges);

		mVertices[x->corner0]->InsertToEdges(edge->Index(), edge);
		mVertices[x->corner1]->InsertToEdges(edge->Index(), edge);

		mEdges.push_back(std::move(edge));
	}

	return std::move(mEdges);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>>
tnbLib::cad2dLib::Modeler_Tools::MakeConsecutive
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
	const Standard_Real theTol
)
{
	const auto corners = MakeCorners(theEdges, theTol);
	const auto edges = MakeConsecutive(corners);

	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner>> 
tnbLib::cad2dLib::Modeler_Tools::MakeCorners
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
	const Standard_Real theTol
)
{
	std::vector<std::shared_ptr<Modeler_Corner>> corners;

	if (theEdges.size() IS_EQUAL 1)
	{
		if (NOT theEdges[0]->IsRing())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Modeler_Corner>> MakeCornes(const std::vector<std::shared_ptr<Pln_Edge>>&)")
				<< "the edge is not a ring!" << endl
				<< abort(FatalError);
		}
		
		auto crn = std::make_shared<Modeler_Corner>(1);
		Debug_Null_Pointer(crn);

		ImportVtxToCorner(theEdges[0]->Vtx0(), crn);
		SetCoordToCorner(theEdges[0]->Vtx0()->Coord(), crn);

		corners.push_back(std::move(crn));

		CalcCornerTolerances(corners);

		return std::move(corners);
	}

	auto b = Pln_Tools::RetrieveBoundingBox(theEdges);
	const auto eB = b.Expanded(b.Diameter()*1.0E-4);

	const auto vertices = Pln_Tools::RetrieveVertices(theEdges);
	Modeler_SrchEng engine;
	engine.SetDomain(eB);
	engine.SetMaxRadius(theTol);

	for (const auto& x : vertices)
	{
		RegisterVtxToSearchEngine(x, engine);
	}

	engine.RetrieveCornersTo(corners);

	CalcCornerTolerances(corners);

	return std::move(corners);
}

void tnbLib::cad2dLib::Modeler_Tools::CalcCornerTolerances
(
	const std::shared_ptr<Modeler_Corner>& theCorner
)
{
	const auto tol = CalcMaxTolerance(theCorner->Coord(), theCorner);
	theCorner->SetRadius(tol);

	const auto& vertices = theCorner->Vertices();
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x.second);
		const auto& vtx = x.second;

		vtx->SetPrecision(tol*2.0);
	}
}

void tnbLib::cad2dLib::Modeler_Tools::CalcCornerTolerances
(
	const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
)
{
	for (const auto& x : theCorners)
	{
		Debug_Null_Pointer(x);
		CalcCornerTolerances(x);
	}
}

void tnbLib::cad2dLib::Modeler_Tools::SetCoordToCorner
(
	const Pnt2d & theCoord,
	const std::shared_ptr<Modeler_Corner>& theCorner
)
{
	Debug_Null_Pointer(theCorner);
	theCorner->SetCoord(theCoord);
}

void tnbLib::cad2dLib::Modeler_Tools::SmoothCorner
(
	const std::shared_ptr<Modeler_Corner>& theCorner
)
{
	Debug_Null_Pointer(theCorner);

	if (NOT theCorner->NbVertices())
	{
		return;
	}

	Pnt2d ctr(0, 0);
	for (const auto& x : theCorner->Vertices())
	{
		Debug_Null_Pointer(x.second);
		const auto& vtx = x.second;

		ctr += vtx->Coord();
	}

	Debug_If_Condition(NOT theCorner->NbVertices());
	ctr /= (Standard_Real)theCorner->NbVertices();

	SetCoordToCorner(ctr, theCorner);

	const auto maxTol = CalcMaxTolerance(ctr, theCorner);
	theCorner->SetTolerance(maxTol);
}

void tnbLib::cad2dLib::Modeler_Tools::ImportVtxToCorner
(
	const std::shared_ptr<Pln_Vertex>& theVtx,
	const std::shared_ptr<Modeler_Corner>& theCorner
)
{
	try
	{
		theCorner->InsertToCorners(theVtx->Index(), theVtx);
	}
	catch (const std::exception&)
	{
		FatalErrorIn("void ImportVtxToCorner(const std::shared_ptr<Pln_Vertex>&, const std::shared_ptr<Modeler_Corner>&)")
			<< "unable to import the vertex into the corner: duplicate data?!" << endl
			<< " check the index: " << theVtx->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::cad2dLib::Modeler_Tools::ImportVtxToSrchEngine
(
	const std::shared_ptr<Pln_Vertex>& theVtx,
	Modeler_SrchEng & theEngine
)
{
#ifdef _DEBUG
	const auto found = theEngine.SelectCorner(theVtx->Coord());
	if (NOT Modeler_SrchEng::IsNull(found))
	{
		FatalErrorIn("void ImportVtxToSrchEngine(const std::shared_ptr<Pln_Vertex>&, Modeler_SrchEng&)")
			<< "it should be no intersection of the vertex with the ones at the engine" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	
	const auto id = theEngine.CornerCounter().RetrieveIndex();
	auto crn = std::make_shared<Modeler_Corner>(id);
	Debug_Null_Pointer(crn);

	crn->SetCoord(theVtx->Coord());

	ImportVtxToCorner(theVtx, crn);

#ifdef _DEBUG
	try
	{
		theEngine.InsertToSrchEngine(crn);
	}
	catch (const std::exception&)
	{
		FatalErrorIn("void ImportVtxToSrchEngine(const std::shared_ptr<Pln_Vertex>&, Modeler_SrchEng&)")
			<< "unable to import the corner into the search engine!" << endl
			<< " check the domain" << endl
			<< abort(FatalError);
	}
#else
	theEngine.InsertToSrchEngine(crn);
#endif // _DEBUG
}

void tnbLib::cad2dLib::Modeler_Tools::RegisterVtxToSearchEngine
(
	const std::shared_ptr<Pln_Vertex>& theVtx,
	Modeler_SrchEng& theEngine
)
{
	const auto radius = theEngine.Radius();
	Debug_If_Condition_Message(radius <= RealFirst(), "the precision is not set!");

	auto b = Entity2d_Box::Box(theVtx->Coord(), radius);
	if (theEngine.IsEmpty())
	{
		ImportVtxToSrchEngine(theVtx, theEngine);
		return;
	}

	const auto selected = theEngine.SelectCorner(theVtx->Coord());
	if (Modeler_SrchEng::IsNull(selected))
	{
		ImportVtxToSrchEngine(theVtx, theEngine);
	}
	else
	{
		ImportVtxToCorner(theVtx, selected);

		/*if (selected->Tolerance() > theEngine.Radius())
		{
			theEngine.SetMaxRadius(selected->Tolerance()*1.05);
		}*/
	}
}
