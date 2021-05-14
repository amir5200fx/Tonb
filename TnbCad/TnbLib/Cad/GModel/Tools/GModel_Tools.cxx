#include <GModel_Tools.hxx>

#include <Cad_GeomSurface.hxx>
#include <GModel_Curve.hxx>
#include <GModel_ParaCurve.hxx>
#include <GModel_Edge.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Surface.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <TopExp_Explorer.hxx>
#include <ShapeFix_Wire.hxx>
#include <BRepTools_WireExplorer.hxx>

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
			for (auto& x : pts)
			{
				x.Transform(trans);
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