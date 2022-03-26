#include <GModel_Tools.hxx>

#include <Cad_Tools.hxx>
#include <Cad_GeomSurface.hxx>
#include <GModel_Curve.hxx>
#include <GModel_ParaCurve.hxx>
#include <GModel_Edge.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Surface.hxx>
#include <GModel_ParaWire.hxx>
#include <GModel_Plane.hxx>
#include <Geo_Tools.hxx>
#include <Pln_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity_Line.hxx>
#include <Vec2d.hxx>
#include <Dir2d.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <TopExp_Explorer.hxx>
#include <ShapeFix_Wire.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

Standard_Boolean 
tnbLib::GModel_Tools::IsPlane
(
	const std::shared_ptr<GModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	return Cad_Tools::IsPlane(theSurface->GeomSurface());
}

Standard_Boolean
tnbLib::GModel_Tools::IsCylinder
(
	const std::shared_ptr<GModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	return Cad_Tools::IsCylinder(theSurface->GeomSurface());
}

Standard_Boolean 
tnbLib::GModel_Tools::IsUniMetric
(
	const std::shared_ptr<GModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	return Cad_Tools::IsUniMetric(theSurface->GeomSurface());
}

std::shared_ptr<tnbLib::GModel_Edge> 
tnbLib::GModel_Tools::GetEdge
(
	const TopoDS_Edge & edge,
	const TopoDS_Face & theFace
)
{
	Standard_Real u0, u1, U0, U1;
	TopLoc_Location pLoc, eLoc;
	auto patch = BRep_Tool::Surface(theFace, pLoc);

	if (NOT BRep_Tool::SameParameter(edge))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameParameter flag" << endl
			<< abort(FatalError);
	}

	if (NOT BRep_Tool::SameRange(edge))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameRange flag" << endl
			<< abort(FatalError);
	}

	auto pCurve0 = BRep_Tool::CurveOnSurface(edge, patch, pLoc, u0, u1);
	auto pCurve = Handle(Geom2d_Curve)::DownCast(pCurve0->Copy());
	auto Curve = BRep_Tool::Curve(edge, eLoc, U0, U1);

	if (edge.Orientation() IS_EQUAL TopAbs_REVERSED)
	{
		auto temp = u1;
		u1 = pCurve->ReversedParameter(u0);
		u0 = pCurve->ReversedParameter(temp);
		pCurve->Reverse();
	}

	auto curveOnPlane = std::make_shared<GModel_ParaCurve>(pCurve);

	if (Curve)
	{
		auto curveOnSurface = std::make_shared<GModel_Curve>(std::move(Curve));
		auto newEdge = std::make_shared<GModel_Edge>(std::move(curveOnPlane), std::move(curveOnSurface));
		return std::move(newEdge);
	}
	else
	{
		auto newEdge = std::make_shared<GModel_Edge>(std::move(curveOnPlane), nullptr);
		return std::move(newEdge);
	}	
}

std::shared_ptr<tnbLib::GModel_Surface>
tnbLib::GModel_Tools::GetSurface(const TopoDS_Face & theFace)
{
	const auto forwardFace = TopoDS::Face(theFace.Oriented(TopAbs_FORWARD));

	auto outterEdges_p = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
	Debug_Null_Pointer(outterEdges_p);

	auto& outterEdges = *outterEdges_p;
	const auto outerWire = BRepTools::OuterWire(forwardFace);
	if (outerWire.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "Null outer wire" << endl
			<< abort(FatalError);
	}

	Standard_Integer id = 0;
	for (
		BRepTools_WireExplorer anEdgeExp(outerWire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		auto edge = TopoDS::Edge(anEdgeExp.Current());
		auto newEdge = GetEdge(edge, forwardFace);
		Debug_Null_Pointer(newEdge);

		newEdge->SetIndex(++id);

		outterEdges.push_back(std::move(newEdge));
	}

	Standard_Integer wireId = 0;

	auto gOuterWire = std::make_shared<GModel_Wire>(std::move(outterEdges_p));
	Debug_Null_Pointer(gOuterWire);

	gOuterWire->SetIndex(++wireId);

	std::shared_ptr<std::vector<std::shared_ptr<GModel_Wire>>> Qwire;
	for (
		TopExp_Explorer aWireExp(forwardFace, TopAbs_WIRE);
		aWireExp.More();
		aWireExp.Next()
		)
	{
		auto wire = TopoDS::Wire(aWireExp.Current());

		if (wire.IsNull()) continue;
		if (wire IS_EQUAL outerWire) continue;
		// has inner wire

		auto innerEdges_p = std::make_shared<std::vector<std::shared_ptr<GModel_Edge>>>();
		Debug_Null_Pointer(innerEdges_p);

		auto& innerEdges = *innerEdges_p;
		for (
			BRepTools_WireExplorer anEdgeExp(wire);
			anEdgeExp.More();
			anEdgeExp.Next()
			)
		{
			auto edge = TopoDS::Edge(anEdgeExp.Current());
			auto newEdge = GetEdge(edge, forwardFace);
			Debug_Null_Pointer(newEdge);

			newEdge->SetIndex(++id);

			innerEdges.push_back(std::move(newEdge));
		}

		if (innerEdges.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the wire is empty!" << endl
				<< abort(FatalError);
		}

		auto gInnerWire = std::make_shared<GModel_Wire>(std::move(innerEdges_p));
		Debug_Null_Pointer(gInnerWire);

		gInnerWire->SetIndex(++wireId);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<GModel_Wire>>>();
		Qwire->push_back(std::move(gInnerWire));
	}

	TopLoc_Location Location;
	auto surface = BRep_Tool::Surface(forwardFace, Location);
	
	auto geometry = std::make_shared<Cad_GeomSurface>(std::move(surface));
	Debug_Null_Pointer(geometry);

	auto face = std::make_shared<GModel_Surface>(std::move(geometry), std::move(gOuterWire), std::move(Qwire));
	return std::move(face);
}

std::vector<std::shared_ptr<tnbLib::GModel_Surface>> 
tnbLib::GModel_Tools::GetSurfaces(const TopoDS_Shape & theShape)
{
	Standard_Integer k = 0;
	std::vector<std::shared_ptr<GModel_Surface>> surfaces;
	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto raw = TopoDS::Face(aFaceExp.Current());

		TopLoc_Location aLoc;
		auto tri = BRep_Tool::Triangulation(raw, aLoc);
		if (tri)
		{
			auto trans = aLoc.Transformation();

			auto& pts = tri->ChangeNodes();
			forThose(i, 1, pts.Size())
			{
				auto x = pts.Value(i);
				x.Transform(trans);

				pts.SetValue(i, x);
			}
		}

		if (raw.IsNull())
		{
			continue;
		}

		auto face = GetSurface(raw);
		Debug_Null_Pointer(face);

		face->SetIndex(++k);

		surfaces.push_back(std::move(face));
	}
	return std::move(surfaces);
}

tnbLib::Entity2d_Box 
tnbLib::GModel_Tools::CalcBoundingBox
(
	const GModel_ParaWire & theWire
)
{
	const auto& curves = theWire.Curves();
	if (curves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve list is empty." << endl
			<< abort(FatalError);
	}
	auto iter = curves.begin();
	auto b = (*iter)->CalcBoundingBox();
	iter++;
	while (iter NOT_EQUAL curves.end())
	{
		b = Geo_BoxTools::Union(b, (*iter)->CalcBoundingBox());
		iter++;
	}
	return std::move(b);
}

namespace tnbLib
{
	namespace repairWire
	{

		// Forward Declarations [2/20/2022 Amir]
		class Link;
		class Segment;
		class Ring;

		class SegmentNodeAdaptor
		{

			/*Private Data*/

			std::weak_ptr<Segment> theBackward_;
			std::weak_ptr<Segment> theForward_;

		protected:

			// default constructor [2/20/2022 Amir]

			SegmentNodeAdaptor()
			{}

			// constructors [2/20/2022 Amir]

		public:

			// public functions and operators [2/20/2022 Amir]

			const auto& BackwardLink() const
			{
				return theBackward_;
			}

			const auto& ForwardLink() const
			{
				return theForward_;
			}

			Standard_Integer NbSegments() const;

			Standard_Boolean IsManifold() const
			{
				return NbSegments() IS_EQUAL 2;
			}

			void SetBackward(const std::shared_ptr<Segment>& theLink)
			{
				theBackward_ = theLink;
			}

			void SetForward(const std::shared_ptr<Segment>& theLink)
			{
				theForward_ = theLink;
			}
		};

		class RingNodeAdaptor
		{

			/*Private Data*/

			std::weak_ptr<Ring> theRing_;

		protected:

			// default constructor [2/20/2022 Amir]

			RingNodeAdaptor()
			{}

			// constructors [2/20/2022 Amir]

		public:

			const auto& GetRing() const
			{
				return theRing_;
			}

			void SetRing(const std::weak_ptr<Ring>& theRing)
			{
				theRing_ = theRing;
			}

		};

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

		protected:

			// default constructor [2/20/2022 Amir]

			Node()
				: theCoord_(Pnt2d::null)
			{}

			// constructors [2/20/2022 Amir]

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

		public:

			// public functions and operators [2/20/2022 Amir]

			const auto& Coord() const
			{
				return theCoord_;
			}

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			void SetCoord(Pnt2d&& theCoord)
			{
				theCoord_ = std::move(theCoord);
			}


			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}
		};

		class RingNode
			: public Node
			, public RingNodeAdaptor
		{

			/*Private Data*/

		public:

			// default constructor [2/20/2022 Amir]

			RingNode()
			{}

			// constructors [2/20/2022 Amir]

			RingNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			RingNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}


			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]
		};

		class SegmentNode
			: public Node
			, public SegmentNodeAdaptor
		{

			/*Private Data*/

		public:

			// default constructor [2/20/2022 Amir]

			SegmentNode()
			{}

			// constructors [2/20/2022 Amir]

			SegmentNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Node(theIndex, theCoord)
			{}

			SegmentNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Node(theIndex, std::move(theCoord))
			{}

			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]

		};

		class Link
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<GModel_ParaCurve> theCurve_;

		protected:

			// default constructor [2/20/2022 Amir]

			Link()
			{}

			// constructors [2/20/2022 Amir]

			Link
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<GModel_ParaCurve>& theCurve
			)
				: Global_Indexed(theIndex)
				, theCurve_(theCurve)
			{}

			Link
			(
				const Standard_Integer theIndex,
				std::shared_ptr<GModel_ParaCurve>&& theCurve
			)
				: Global_Indexed(theIndex)
				, theCurve_(std::move(theCurve))
			{}

		public:

			// public functions and operators [2/20/2022 Amir]

			const auto& GetCurve() const
			{
				return theCurve_;
			}

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}

		};

		class Segment
			: public Link
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			// default constructor [2/20/2022 Amir]

			Segment()
			{}

			// constructors [2/20/2022 Amir]

			Segment
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<GModel_ParaCurve>& theCurve,
				const std::shared_ptr<Node>& theNode0, 
				const std::shared_ptr<Node>& theNode1
			)
				: Link(theIndex, theCurve)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			Segment
			(
				const Standard_Integer theIndex, 
				std::shared_ptr<GModel_ParaCurve>&& theCurve,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1
			)
				: Link(theIndex, std::move(theCurve))
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
			{}

			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]

			

			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			void SetNode0(const std::shared_ptr<Node>& theNode)
			{
				theNode0_ = theNode;
			}

			void SetNode1(const std::shared_ptr<Node>& theNode)
			{
				theNode1_ = theNode;
			}

			void SetNode0(std::shared_ptr<Node>&& theNode)
			{
				theNode0_ = std::move(theNode);
			}

			void SetNode1(std::shared_ptr<Node>&& theNode)
			{
				theNode1_ = std::move(theNode);
			}

		};

		class Ring
			: public Link
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode_;

		public:

			// default constructor [2/20/2022 Amir]

			Ring()
			{}

			// constructors [2/20/2022 Amir]

			Ring
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<GModel_ParaCurve>& theCurve, 
				const std::shared_ptr<Node>& theNode
			)
				: Link(theIndex, theCurve)
				, theNode_(theNode)
			{}

			Ring
			(
				const Standard_Integer theIndex, 
				std::shared_ptr<GModel_ParaCurve>&& theCurve, 
				std::shared_ptr<Node>&& theNode
			)
				: Link(theIndex, std::move(theCurve))
				, theNode_(std::move(theNode))
			{}

			// override functions and operators [2/20/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			// public functions and operators [2/20/2022 Amir]

			const auto& GetNode() const
			{
				return theNode_;
			}

			void SetNode(const std::shared_ptr<Node>& theNode)
			{
				theNode_ = theNode;
			}

			void SetNode(std::shared_ptr<Node>&& theNode)
			{
				theNode_ = std::move(theNode);
			}


		};

		enum class CurvePoint
		{
			start,
			end
		};

		static auto GetParameter
		(
			const std::shared_ptr<GModel_ParaCurve>& theCurve, 
			const CurvePoint thePoint
		)
		{
			Standard_Real u = 0;
			if (thePoint IS_EQUAL CurvePoint::end)
			{
				u = theCurve->LastParameter();
			}
			else if (thePoint IS_EQUAL CurvePoint::start)
			{
				u = theCurve->FirstParameter();
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid type of point has been detected!" << endl
					<< abort(FatalError);
			}
			return u;
		}

		static auto CalcTangent
		(
			const std::shared_ptr<GModel_ParaCurve>& theCurve,
			const CurvePoint thePoint
		)
		{
			Pnt2d pt;
			Vec2d vec;

			Debug_Null_Pointer(theCurve);
			
			const auto& geom = theCurve->Geometry();
			Debug_Null_Pointer(geom);

			geom->D1(GetParameter(theCurve, thePoint), pt, vec);
			auto t = std::make_pair(std::move(pt), std::move(vec));
			return std::move(t);
		}

		static auto CalcIntersectionPoint
		(
			const Pnt2d& thePoint0, 
			const Vec2d& theTang0, 
			const Pnt2d& thePoint1, 
			const Vec2d& theTang1
		)
		{
			const auto p0 = thePoint0;
			const auto p1 = thePoint1;
			const Dir2d d0 = theTang0;
			const Dir2d d1 = theTang1;
			
			Entity2d_Line line0(std::move(p0), std::move(d0));
			Entity2d_Line line1(std::move(p1), std::move(d1));

			auto entity = Geo_Tools::Intersection_cgal(line0, line1);
			if (NOT entity->IsPoint())
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid type of geometry has been detected!" << endl
					<< abort(FatalError);
			}
			auto ptEnt = std::dynamic_pointer_cast<Geo_Tools::PointIntersectEntity2d>(entity);
			Debug_Null_Pointer(ptEnt);

			auto& pt = ptEnt->IntPnt;
			return std::move(pt);
		}

		static void CheckTolerance(const Pnt2d& theCentre, const Pnt2d& thePt, const Standard_Real theTol)
		{
			if (theCentre.Distance(thePt) >= theTol)
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid wire under the tolerance has been detected." << endl
					<< " - tolerance: " << theTol << endl
					<< abort(FatalError);
			}
		}

		static auto ProjectPoint(const Pnt2d& theCoord, const std::shared_ptr<GModel_ParaCurve>& theCurve)
		{
			Debug_Null_Pointer(theCurve);
			Geom2dAPI_ProjectPointOnCurve alg(theCoord, theCurve->Geometry());
			Pnt2d pt = alg.NearestPoint();
			auto t = std::make_pair(std::move(pt), alg.LowerDistanceParameter());
			return std::move(t);
		}

		static auto SplitFirstOfCurve(const Pnt2d& theCoord, const std::shared_ptr<GModel_ParaCurve>& theCurve)
		{
			const auto[ppt, u] = ProjectPoint(theCoord, theCurve);
			if (std::abs(u - theCurve->FirstParameter()) <= gp::Resolution())
			{
				auto t = std::make_pair(theCurve, Standard_False);
				return std::move(t);
			}
			Handle(Geom2d_Curve) c0, c1;
			Pln_Tools::SplitCurve(theCurve->Geometry(), u, c0, c1);

			auto c = std::make_shared<GModel_ParaCurve>(theCurve->Index(), theCurve->Name(), std::move(c1));
			auto t = std::make_pair(std::move(c), Standard_True);
			return std::move(t);
		}

		static auto SplitLastOfCurve(const Pnt2d& theCoord, const std::shared_ptr<GModel_ParaCurve>& theCurve)
		{
			const auto[ppt, u] = ProjectPoint(theCoord, theCurve);
			if (std::abs(u - theCurve->LastParameter()) <= gp::Resolution())
			{
				auto t = std::make_pair(theCurve, Standard_False);
				return std::move(t);
			}
			Handle(Geom2d_Curve) c0, c1;
			Pln_Tools::SplitCurve(theCurve->Geometry(), u, c0, c1);

			auto c = std::make_shared<GModel_ParaCurve>(theCurve->Index(), theCurve->Name(), std::move(c0));
			auto t = std::make_pair(std::move(c), Standard_True);
			return std::move(t);
		}

		static auto SplitCurve(const Pnt2d& theCoord, const std::shared_ptr<GModel_ParaCurve>& theCurve, const CurvePoint thePt)
		{
			if (thePt IS_EQUAL CurvePoint::start)
			{
				auto t = SplitFirstOfCurve(theCoord, theCurve);
				return std::move(t);
			}
			else if (thePt IS_EQUAL CurvePoint::end)
			{
				auto t = SplitLastOfCurve(theCoord, theCurve);
				return std::move(t);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unspecified type of point has been detected!" << endl
					<< abort(FatalError);
			}
			std::shared_ptr<GModel_ParaCurve> c;
			auto t = std::make_pair(std::move(c), Standard_True);
			return std::move(t);
		}

		static auto CalcCornerPoint(const std::shared_ptr<GModel_ParaCurve>& theCurve0, const std::shared_ptr<GModel_ParaCurve>& theCurve1)
		{
			const auto[P0, t0] = CalcTangent(theCurve0, CurvePoint::end);
			const auto[P1, t1] = CalcTangent(theCurve1, CurvePoint::start);

			auto coord = CalcIntersectionPoint(P0, t0, P1, t1);
			return std::move(coord);
		}

		static auto TrimCornerCurves(const std::shared_ptr<GModel_ParaCurve>& theCurve0, const std::shared_ptr<GModel_ParaCurve>& theCurve1)
		{
			const auto coord = CalcCornerPoint(theCurve0, theCurve1);
			auto[c0, trimmed0] = SplitCurve(coord, theCurve0, CurvePoint::end);
			auto[c1, trimmed1] = SplitCurve(coord, theCurve1, CurvePoint::start);
			auto t = std::make_pair(std::move(c0), std::move(c1));
			return std::move(t);
		}

		static auto MaxIndex(const std::vector<std::shared_ptr<GModel_ParaCurve>>& theCurves)
		{
			auto iter = theCurves.begin();
			auto maxIndex = (*iter)->Index();
			iter++;
			while (iter NOT_EQUAL theCurves.end())
			{
				auto id = (*iter)->Index();
				if (id > maxIndex)
				{
					maxIndex = id;
				}
				iter++;
			}
			return maxIndex;
		}

		static void CheckDuplicateIndex(const std::vector<std::shared_ptr<GModel_ParaCurve>>& theCurves)
		{
			const auto maxIndex = MaxIndex(theCurves);
			std::vector<Standard_Integer> curves(maxIndex + 1, 0);
			for (const auto& x : theCurves)
			{
				Debug_Null_Pointer(x);
				if (curves.at(x->Index()))
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate index has been detected!" << endl
						<< abort(FatalError);
				}
				curves.at(x->Index()) = 1;
			}
		}

		static auto TrimCurves(const std::vector<std::shared_ptr<GModel_ParaCurve>>& theCurves)
		{
			if (theCurves.size() < 1)
			{
				FatalErrorIn(FunctionSIG)
					<< "not enough number of curves has been detected!" << endl
					<< abort(FatalError);
			}
			const auto maxIndex = MaxIndex(theCurves);
			std::vector<std::shared_ptr<GModel_ParaCurve>> curves(maxIndex + 1);

			const auto& c0 = theCurves.at(curves.size() - 1);
			const auto& c1 = theCurves.at(0);

			Debug_Null_Pointer(c0);
			Debug_Null_Pointer(c1);

			auto[sub0, sub1] = TrimCornerCurves(c0, c1);
			Debug_Null_Pointer(sub0);
			Debug_Null_Pointer(sub1);

			curves.at(sub0->Index()) = std::move(sub0);
			curves.at(sub1->Index()) = std::move(sub1);

			for (size_t i = 1; i < theCurves.size(); i++)
			{
				const auto& c0 = curves.at(i - 1);
				const auto& c1 = curves.at(i);

				Debug_Null_Pointer(c0);
				Debug_Null_Pointer(c1);

				auto curve0 = c0;
				if (curves.at(c0->Index()))
				{
					curve0 = curves.at(c0->Index());
				}

				auto curve1 = c1;
				if (curves.at(c1->Index()))
				{
					curve1 = curves.at(c1->Index());
				}

				auto[sub0, sub1] = TrimCornerCurves(curve0, curve1);
				Debug_Null_Pointer(sub0);
				Debug_Null_Pointer(sub1);

				curves.at(sub0->Index()) = std::move(sub0);
				curves.at(sub1->Index()) = std::move(sub1);
			}

			std::vector<std::shared_ptr<GModel_ParaCurve>> trimmed;
			trimmed.reserve(theCurves.size());
			for (const auto& x : curves)
			{
				if (x)
				{
					trimmed.push_back(x);
				}
			}
			return std::move(trimmed);
		}

		static auto CreateNode
		(
			const std::shared_ptr<GModel_ParaCurve>& theCurve0, 
			const std::shared_ptr<GModel_ParaCurve>& theCurve1,
			const Standard_Real theTol
		)
		{
			/*const auto[P0, t0] = CalcTangent(theCurve0, CurvePoint::end);
			const auto[P1, t1] = CalcTangent(theCurve1, CurvePoint::start);

			const auto coord = CalcIntersectionPoint(P0, t0, P1, t1);*/

			const auto P0 = theCurve0->LastCoord();
			const auto P1 = theCurve1->FirstCoord();

			const auto coord = MEAN(P0, P1);

			//CheckTolerance(coord, P0, theTol);
			//CheckTolerance(coord, P1, theTol);

			auto node = std::make_shared<SegmentNode>(0, std::move(coord));
			return std::move(node);
		}

		static auto CreateWire(const std::shared_ptr<GModel_ParaCurve>& theCurve, const Standard_Real theTol)
		{
			Debug_Null_Pointer(theCurve);
			std::vector<std::shared_ptr<Link>> links;
			auto P0 = theCurve->FirstCoord();
			auto P1 = theCurve->LastCoord();
			auto Pm = MEAN(P0, P1);

			//CheckTolerance(Pm, P0, theTol);
			auto node = std::make_shared<RingNode>(1, std::move(Pm));

			auto curve = theCurve;
			auto edge = std::make_shared<Ring>(1, std::move(curve), std::move(node));

			if (Pm.Distance(P0) <= theTol)
			{
				node->SetRing(edge);
			}
			links.push_back(std::move(edge));
			return std::move(links);
		}

		static auto CreateWire(const std::vector<std::shared_ptr<GModel_ParaCurve>>& theCurves, const Standard_Real theTol)
		{
			std::vector<std::shared_ptr<SegmentNode>> nodes;
			nodes.reserve(theCurves.size());
			for (size_t i = 1; i < theCurves.size(); i++)
			{
				const auto& curve0 = theCurves.at(i - 1);
				const auto& curve1 = theCurves.at(i);

				Debug_Null_Pointer(curve0);
				Debug_Null_Pointer(curve1);

				auto node = CreateNode(curve0, curve1, theTol);
				Debug_Null_Pointer(node);
				node->SetIndex((Standard_Integer)i);

				nodes.push_back(std::move(node));
			}

			std::vector<std::shared_ptr<Link>> links;
			links.reserve(theCurves.size());
			Standard_Integer k = 1;
			for (const auto& x : theCurves)
			{
				Debug_Null_Pointer(x);

				const auto& node0 = nodes.at(k - 1);
				const auto& node1 = nodes.at(k);
				Debug_Null_Pointer(node0);
				Debug_Null_Pointer(node1);

				auto edge = std::make_shared<Segment>(k, x, node0, node1);
				Debug_Null_Pointer(edge);

				auto v0 = x->FirstCoord();
				auto v1 = x->LastCoord();

				if (v0.Distance(node0->Coord()) <= theTol)
				{
					node0->SetForward(edge);
				}

				if (v1.Distance(node1->Coord()) <= theTol)
				{
					node1->SetBackward(edge);
				}	

				links.push_back(std::move(edge));
			}
			return std::move(links);
		}

		static auto CreateWire(const std::shared_ptr<GModel_ParaWire>& theWire, const Standard_Real theTol)
		{
			Debug_Null_Pointer(theWire);
			if (theWire->Curves().empty())
			{
				FatalErrorIn(FunctionSIG)
					<< " the edge list is empty" << endl
					<< abort(FatalError);
			}
			const auto& curves = theWire->Curves();
			if (curves.size() IS_EQUAL 1)
			{
				auto links = CreateWire(curves.at(0), theTol);
				return std::move(links);
			}
			else
			{
				auto links = CreateWire(curves, theTol);
				return std::move(links);
			}
		}

		static void CheckWire(const std::vector<std::shared_ptr<Link>>& theLinks)
		{
			if (theLinks.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid wire has been detected!" << endl
					<< abort(FatalError);
			}
			if (theLinks.size() IS_EQUAL 1)
			{
				auto ring = std::dynamic_pointer_cast<Ring>(theLinks.at(0));
				Debug_Null_Pointer(ring);
				auto node = std::dynamic_pointer_cast<RingNode>(ring->GetNode());
				Debug_Null_Pointer(node);
				if (NOT node->GetRing().lock())
				{
					FatalErrorIn(FunctionSIG)
						<< "not-manifold type of wire is detected!" << endl
						<< abort(FatalError);
				}
			}
			else
			{
				for (const auto& x : theLinks)
				{
					Debug_Null_Pointer(x);
					auto seg = std::dynamic_pointer_cast<Segment>(x);
					Debug_Null_Pointer(seg);

					auto node0 = std::dynamic_pointer_cast<SegmentNode>(seg->Node0());
					Debug_Null_Pointer(node0);

					if (NOT node0->IsManifold())
					{
						FatalErrorIn(FunctionSIG)
							<< "not-manifold type of wire is detected!" << endl
							<< abort(FatalError);
					}
				}
			}
		}

		static auto CreateWire(const std::vector<std::shared_ptr<Link>>& theLinks)
		{
			std::vector<std::shared_ptr<GModel_ParaCurve>> curves;
			curves.reserve(theLinks.size());
			for (const auto& x : theLinks)
			{
				Debug_Null_Pointer(x);
				curves.push_back(x->GetCurve());
			}
			auto curvesPtr = std::make_shared<std::vector<std::shared_ptr<GModel_ParaCurve>>>(std::move(curves));
			auto wire = std::make_shared<GModel_ParaWire>(std::move(curvesPtr));
			return std::move(wire);
		}
	}
}

Standard_Integer 
tnbLib::repairWire::SegmentNodeAdaptor::NbSegments() const
{
	Standard_Integer nbSegments = 0;
	if (ForwardLink().lock())
		nbSegments++;
	if (BackwardLink().lock())
		nbSegments++;
	return nbSegments;
}

std::shared_ptr<tnbLib::GModel_ParaWire> 
tnbLib::GModel_Tools::TrimWire
(
	const std::shared_ptr<GModel_ParaWire>& theWire
)
{
	Debug_Null_Pointer(theWire);
	if (theWire->Curves().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< " the edge list is empty" << endl
			<< abort(FatalError);
	}
	const auto& curves = theWire->Curves();
	if (curves.size() > 1)
	{
		auto trimmed = repairWire::TrimCurves(curves);
		auto trimmedPtr = std::make_shared<std::vector<std::shared_ptr<GModel_ParaCurve>>>(std::move(trimmed));
		auto wire = std::make_shared<GModel_ParaWire>(theWire->Index(), theWire->Name(), std::move(trimmedPtr));
		return std::move(wire);
	}
	// no changing is applied to the wire with one curve [2/21/2022 Amir]
	return theWire;
}

std::shared_ptr<tnbLib::GModel_ParaWire> 
tnbLib::GModel_Tools::GetOuterParaWire
(
	const std::shared_ptr<GModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	const auto& outerWire = theSurface->Outer();
	if (NOT outerWire)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of surface has been detected!" << endl
			<< abort(FatalError);
	}
	auto wire = GModel_Wire::RetrieveParaWire(*outerWire);
	return std::move(wire);
}

std::vector<std::shared_ptr<tnbLib::GModel_ParaWire>> 
tnbLib::GModel_Tools::GetInnerParaWires
(
	const std::shared_ptr<GModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	const auto& inners = theSurface->Inner();
	std::vector<std::shared_ptr<GModel_ParaWire>> wires;
	for (const auto& x : *inners)
	{
		Debug_Null_Pointer(x);
		auto wire = GModel_Wire::RetrieveParaWire(*x);
		wires.push_back(std::move(wire));
	}
	return std::move(wires);
}

std::shared_ptr<tnbLib::GModel_Plane> 
tnbLib::GModel_Tools::GetParaPlane
(
	const std::shared_ptr<GModel_Surface>& theSurface,
	const Standard_Real theTol
)
{
	Debug_Null_Pointer(theSurface);
	const auto unRepOuterWire = GetOuterParaWire(theSurface);
	if (NOT unRepOuterWire)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid surface type has been detected: " << endl
			<< " - the surface has no outer wire!" << endl
			<< abort(FatalError);
	}

	const auto trimOuterWire = TrimWire(unRepOuterWire);
	Debug_Null_Pointer(trimOuterWire);

	const auto outerEdges = repairWire::CreateWire(trimOuterWire, theTol);
	repairWire::CheckWire(outerEdges);

	auto outerWire = repairWire::CreateWire(outerEdges);
	Debug_Null_Pointer(outerWire);

	auto innerWires = std::make_shared<GModel_Plane::wireList>();
	auto unRepinnerWires = GetInnerParaWires(theSurface);
	if (unRepinnerWires.size())
	{
		for (const auto& x : unRepinnerWires)
		{
			Debug_Null_Pointer(x);

			auto trimInnerWire = TrimWire(x);
			Debug_Null_Pointer(trimInnerWire);

			auto innerEdges = repairWire::CreateWire(trimInnerWire, theTol);
			repairWire::CheckWire(innerEdges);

			auto innerWire = repairWire::CreateWire(innerEdges);
			Debug_Null_Pointer(innerWire);

			innerWires->push_back(std::move(innerWire));
		}
	}
	auto plane = std::make_shared<GModel_Plane>(std::move(outerWire), std::move(innerWires));
	return std::move(plane);
}