#include <Cad2d_Modeler_Tools.hxx>

#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad2d_Modeler_SrchEng.hxx>
#include <Cad2d_Modeler_Corner.hxx>
#include <Cad2d_Modeler_Segment.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Curve.hxx>

#include <algorithm>

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeEdge
(
	const Handle(Geom2d_Curve)& geom, 
	const Pnt2d & p0, 
	const Pnt2d & p1
)
{
	auto v0 = std::make_shared<Pln_Vertex>(0, p0);
	Debug_Null_Pointer(v0);

	auto v1 = std::make_shared<Pln_Vertex>(1, p1);
	Debug_Null_Pointer(v1);

	auto curve = std::make_shared<Pln_Curve>(0, geom);
	Debug_Null_Pointer(curve);

	auto edge = std::make_shared<Pln_Segment>(std::move(v0), std::move(v1), std::move(curve));
	Debug_Null_Pointer(edge);

	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::cad2dLib::Modeler_Tools::MakeRing
(
	const Handle(Geom2d_Curve)& geom,
	const Pnt2d & theP
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

std::shared_ptr<tnbLib::cad2dLib::Modeler_Segment>
tnbLib::cad2dLib::Modeler_Tools::HasRing
(
	const std::shared_ptr<Modeler_Corner>& theCrn
)
{
	if (NOT theCrn->NbSegments())
	{
		return nullptr;
	}
	for (const auto& x : theCrn->Segments())
	{
		Debug_Null_Pointer(x.second.lock());
		auto seg = x.second.lock();
		if (seg->IsRing())
		{
			return std::move(seg);
		}
	}
	return nullptr;
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Segment>
tnbLib::cad2dLib::Modeler_Tools::IsSegment
(
	const std::shared_ptr<Modeler_Corner>& theCrn0,
	const std::shared_ptr<Modeler_Corner>& theCrn1
)
{
	Debug_Null_Pointer(theCrn0);
	Debug_Null_Pointer(theCrn1);

	if (theCrn0->NbSegments() <= theCrn1->NbSegments())
	{
		if (NOT theCrn0->NbSegments())
		{
			return nullptr;
		}

		const auto& segments = theCrn0->Segments();
		for (const auto& x : segments)
		{
			auto segmnt = x.second.lock();

			Debug_Null_Pointer(segmnt);
			if (theCrn1->IsContains(segmnt))
			{
				return std::move(segmnt);
			}
		}
		return nullptr;
	}
	else
	{
		const auto segmnt = IsSegment(theCrn1, theCrn0);
		return std::move(segmnt);
	}
}



std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	auto curve = Pln_CurveTools::MakeSegment(theP0, theP1);
	if (curve)
	{
		auto edge = MakeEdge(curve, theP0, theP1);
		Debug_Null_Pointer(edge);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	/*const auto V = theLength* gp_Dir2d(cos(theAngle), sin(theAngle));
	Pnt2d P1(theP0.X() + V.X(), theP0.Y() + V.Y());*/
	auto edge = MakeSegment(theP0, /*P1*/theP0 + theLength * Dir2d(cos(theAngle), sin(theAngle)));
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
	auto geom = Pln_CurveTools::MakeCircArc(theP0, theP1, theP2);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircArc(theP0, theV0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircArc(theCirc, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircArc(theCirc, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeElipsArc(theElips, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeElipsArc(theElips, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeHyprArc(theHypr, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeHyprArc(theHypr, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeParbArc
(
	const gp_Parab2d & theParab, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	auto geom = Pln_CurveTools::MakeParbArc(theParab, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeParabArc
(
	const gp_Parab2d & theParab,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	auto geom = Pln_CurveTools::MakeParbArc(theParab, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & c
)
{
	auto geom = Pln_CurveTools::MakeCircle(c);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircle(C, theP);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircle(theP0, theP1, theP2);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircle(theC, theRadius);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeCircle(theC, theP);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::cad2dLib::Modeler_Tools::MakeEllipse
(
	const gp_Elips2d & E
)
{
	auto geom = Pln_CurveTools::MakeEllipse(E);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
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
	auto geom = Pln_CurveTools::MakeEllipse(theS0, theS1, theCenter);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter())
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::Interpolation
(
	const std::vector<Pnt2d>& theQ,
	const Standard_Boolean thePeriodic,
	const Standard_Real theTol
)
{
	auto geom = Pln_CurveTools::Interpolation(theQ, thePeriodic, theTol);
	auto edge = 
		MakeEdge
		(
			geom, 
			geom->Value(geom->FirstParameter()),
			geom->Value(geom->LastParameter())
		);
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::Interpolation
(
	const std::vector<Pnt2d>& theQ, 
	const Vec2d & theFirst, 
	const Vec2d & theLast, 
	const Standard_Boolean thePeriodic, 
	const Standard_Real theTol, 
	const Standard_Boolean theScale
)
{
	auto geom = 
		Pln_CurveTools::Interpolation
		(
			theQ, theFirst, theLast,
			thePeriodic, theTol, theScale
		);
	auto edge =
		MakeEdge
		(
			geom,
			geom->Value(geom->FirstParameter()),
			geom->Value(geom->LastParameter())
		);
	return std::move(edge);
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
	namespace cad2dLib
	{
		std::shared_ptr<Modeler_Corner> 
			NextCorner
			(
				const std::shared_ptr<Modeler_Corner>& theCrn, 
				const char* funName
			)
		{
			if (theCrn->NbSegments() NOT_EQUAL 1)
			{
				FatalErrorIn(funName)
					<< "the shape is no manifold!" << endl
					<< abort(FatalError);
			}

			auto segmnt = theCrn->Segments().begin()->second.lock();
			Debug_Null_Pointer(segmnt);

			return segmnt->Other(theCrn);
		}

		std::shared_ptr<Modeler_Segment>
			NextSegment
			(
				const std::shared_ptr<Modeler_Corner>& theCrn,
				const char* funName
			)
		{
			const auto& segments = theCrn->Segments();
			if (segments.size() NOT_EQUAL 1)
			{
				FatalErrorIn(funName)
					<< " the shape is not manifold" << endl
					<< " nb. of segments = " << (label)segments.size() << endl
					<< abort(FatalError);
			}

			auto segmnt = segments.begin()->second.lock();
			return std::move(segmnt);
		}

		/*std::vector<std::shared_ptr<Modeler_Segment>> RetrieveRing(const std::shared_ptr<Modeler_Corner>& theCrn)
		{

		}*/

		void RegisterToMap
		(
			std::shared_ptr<Modeler_Segment>&& theSeg, 
			std::map<Standard_Integer, std::shared_ptr<Modeler_Segment>>& theMap
		)
		{
			auto paired = std::make_pair(theSeg->Index(), std::move(theSeg));
			auto insert = theMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< " index = " << theSeg->Index() << endl
					<< abort(FatalError);
			}
		}
	}
}

//std::vector<std::shared_ptr<tnbLib::cad2dLib::Modeler_Segment>> 
//tnbLib::cad2dLib::Modeler_Tools::TrackRing
//(
//	const std::shared_ptr<Modeler_Corner>& theCrn
//)
//{
//	const auto& segments = theCrn->Segments();
//	if (segments.size() IS_EQUAL 1)
//	{
//		auto ring = ::tnbLib::cad2dLib::RetrieveRing(theCrn);
//		return std::move(ring);
//	}
//
//	if (segments.size() NOT_EQUAL 1)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< " the shape is not manifold" << endl
//			<< " nb. of segments = " << (label)segments.size() << endl
//			<< abort(FatalError);
//	}
//
//	std::map<Standard_Integer, std::shared_ptr<Modeler_Segment>> regSegments;
//	auto segmnt = segments.begin()->second.lock();
//
//	if (theCrn->RemoveFromSegments(segmnt->Index()).lock() NOT_EQUAL segmnt)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "contradictory data!" << endl
//			<< abort(FatalError);
//	}
//
//	auto next =
//		::tnbLib::cad2dLib::NextCorner
//		(
//			theCrn,
//			"std::vector<std::shared_ptr<Modeler_Segment>> TrackRing(const std::shared_ptr<Modeler_Corner>&)"
//		);
//
//	while (next)
//	{
//		::tnbLib::cad2dLib::RegisterToMap(std::move(segmnt), regSegments);
//
//
//	}
//	
//}

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
		const auto v0 = theEdge->FirstVtx();
		Debug_Null_Pointer(v0);

		const auto v1 = theEdge->LastVtx();
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


			Standard_Boolean 
				IsInside
				(
					const std::shared_ptr<Pln_Vertex>& theVtx
				) const
			{
				if (vtx0 IS_EQUAL theVtx) return Standard_True;
				if (vtx1 IS_EQUAL theVtx) return Standard_True;
				return Standard_False;
			}
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

				auto piter = paired.find(x->LastVtx()->Index());
				if (piter IS_EQUAL paired.end())
				{
					v0 = x->LastVtx();
				}
				else
				{
					v0 = x->FirstVtx();
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
				auto k0 = k - 1;
				if (k0 < 0) k0 = (int)theEdges.size() - 1;

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

#include <Adt_AvlTree.hxx>



//std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
//tnbLib::cad2dLib::Modeler_Tools::RetrieveWires
//(
//	const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
//)
//{
//	Adt_AvlTree<std::shared_ptr<Modeler_Corner>> crnReg;
//	crnReg.SetComparableFunction(&Modeler_Corner::IsLess);
//
//	crnReg.Insert(theCorners);
//
//
//}

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

	std::map
		<
		Standard_Integer,
		std::shared_ptr<mergeFunLib::Corner>
		> indexToCornerMap;

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

		auto paired = std::make_pair(vtx->Index(), x);
		auto insert = indexToCornerMap.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data!" << endl
				<< abort(FatalError);
		}

		mVertices.push_back(std::move(vtx));
	}

	std::vector<std::shared_ptr<Pln_Edge>> mEdges;
	mEdges.reserve(segments.size());

	Standard_Integer nbEdges = 0;
	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x);

		const auto& crn0 = indexToCornerMap[mVertices[x->corner0]->Index()];

		Standard_Boolean reversed = Standard_False;
		if (NOT crn0->IsInside(x->edge->FirstVtx()))
		{
			reversed = Standard_True;
		}

		auto edge = std::make_shared<Pln_Segment>
			(
				mVertices[x->corner0], mVertices[x->corner1],
				x->edge->Curve(),
				(reversed ? !x->edge->Sense() : x->edge->Sense()));
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

		ImportVtxToCorner(theEdges[0]->FirstVtx(), crn);
		SetCoordToCorner(theEdges[0]->FirstVtx()->Coord(), crn);

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

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::cad2dLib::Modeler_Tools::ConstructMergedEdges
(
	const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
)
{
	std::map<Standard_Integer, std::pair<Standard_Integer, Standard_Integer>>
		edgesMap;
	std::map<Standard_Integer, std::shared_ptr<Pln_Edge>>
		idToEdgeMap;
	for (const auto& x : theCorners)
	{
		for (const auto& v : x->Vertices())
		{
			Debug_Null_Pointer(v.second);
			const auto& vertex = v.second;

			for (const auto& e : vertex->Edges())
			{
				Debug_Null_Pointer(e.second.lock());
				auto edge = e.second.lock();

				auto iter = edgesMap.find(edge->Index());
				if (iter IS_EQUAL edgesMap.end())
				{
					edgesMap[edge->Index()] = std::make_pair(-1, -1);
					idToEdgeMap[edge->Index()] = edge;
					iter = edgesMap.find(edge->Index());
				}

				if (edge->FirstVtx() IS_EQUAL vertex)
				{
					iter->second.first = x->Index();
				}
				if (edge->LastVtx() IS_EQUAL vertex)
				{
					iter->second.second = x->Index();
				}
			}
		}
	}

	std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>> verticesMap;
	for (const auto& x : theCorners)
	{
		if (NOT x->NbVertices()) continue;
		auto vtx = std::make_shared<Pln_Vertex>(x->Index(), x->Name(), x->CalcMeanCoord());
		Debug_Null_Pointer(vtx);

		auto paired = std::make_pair(x->Index(), std::move(vtx));
		auto insert = verticesMap.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "unable to insert the item into the map: duplicate data!" << endl
				<< abort(FatalError);
		}
	}

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(edgesMap.size());
	for (const auto& x : edgesMap)
	{
		const auto& ids = x.second;
		auto v0 = ids.first;
		auto v1 = ids.second;

		const auto& pEdge = idToEdgeMap[x.first];

		if (v0 IS_EQUAL v1)
		{
			const auto& vtx0 = verticesMap[v0];

			auto edge = std::make_shared<Pln_Ring>
				(
					pEdge->Index(), pEdge->Name(),
					vtx0, pEdge->Curve(),
					pEdge->Sense()
					);
			Debug_Null_Pointer(edge);

			edge->Mesh() = pEdge->Mesh();

			vtx0->InsertToEdges(edge->Index(), edge);

			edges.push_back(std::move(edge));
		}
		else
		{
			const auto& vtx0 = verticesMap[v0];
			const auto& vtx1 = verticesMap[v1];

			auto edge = std::make_shared<Pln_Segment>
				(
					pEdge->Index(), pEdge->Name(),
					vtx0, vtx1, pEdge->Curve(),
					pEdge->Sense()
					);
			Debug_Null_Pointer(edge);

			edge->Mesh() = pEdge->Mesh();

			vtx0->InsertToEdges(edge->Index(), edge);
			vtx1->InsertToEdges(edge->Index(), edge);
			
			edges.push_back(std::move(edge));
		}
	}
	return std::move(edges);
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
