#include "Tools.hxx"


#include <Pln_CurveTools.hxx>
#include <Dir2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <TopoDS.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRep_Builder.hxx>
#include <BRepLib.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GC_MakeSegment.hxx>
#include <GeomProjLib.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <TColgp_HArray1OfPnt.hxx>

//std::vector<tnbLib::Pnt3d> 
//tnbLib::Tools::CalcPnt3ds
//(
//	const Standard_Real z0,
//	const gp_Ax1& theAx,
//	const Standard_Real theRadius,
//	const Standard_Real thePhi
//)
//{
//	
//}

std::vector<tnbLib::Pnt3d> 
tnbLib::Tools::CalcPnt3ds
(
	const Standard_Real z0, 
	const std::vector<Standard_Real>& theZs,
	const Standard_Real theRadius,
	const Standard_Real thePhi
)
{
	auto x = theRadius * std::cos(thePhi);
	auto y = theRadius * std::sin(thePhi);
	std::vector<Pnt3d> coords;
	coords.reserve(theZs.size());
	for (auto z : theZs)
	{
		Pnt3d pt(x, y, z + z0);
		coords.push_back(std::move(pt));
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::Tools::CalcPnt3ds
(
	const std::vector<Pnt2d>& thePts,
	const Handle(Geom_Surface)& theSurf
)
{
	std::vector<Pnt3d> Pts;
	Pts.reserve(thePts.size());
	for (const auto& x : thePts)
	{
		auto pt = theSurf->Value(x.X(), x.Y());
		Pts.push_back(std::move(pt));
	}
	return std::move(Pts);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Tools::ProjectPointsToCylinderSurf
(
	const std::vector<Pnt3d>& theCoords,
	const Handle(Geom_Surface)& theSurf
)
{
	GeomAPI_ProjectPointOnSurf prj;
	std::vector<Pnt2d> coords_2d;
	coords_2d.reserve(theCoords.size());
	for (const auto& x : theCoords)
	{
		prj.Init(x, theSurf);
		Standard_Real u, v;
		prj.LowerDistanceParameters(u, v);

		Pnt2d p2(u, v);
		coords_2d.push_back(std::move(p2));
	}
	return std::move(coords_2d);
}

Handle(Geom2d_Curve) 
tnbLib::Tools::ProjectCurveOnSurf
(
	const Handle(Geom_Curve)& theC3,
	const Handle(Geom_Surface)& theSurf
)
{
	auto c2 =
		GeomProjLib::Curve2d(theC3, theSurf);
	if (NOT c2)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane." << endl
			<< abort(FatalError);
	}
	return std::move(c2);
}

std::vector<tnbLib::Pnt3d> 
tnbLib::Tools::CalcCrackPoints
(
	const std::vector<Pnt3d>& thePnts, 
	const std::vector<Standard_Real>& theDs, 
	const gp_Ax1& theAx
)
{
	Handle(Geom_Curve) line = new Geom_Line(theAx);
	std::vector<Pnt3d> pPts;
	for (const auto& x : thePnts)
	{
		GeomAPI_ProjectPointOnCurve prj(x, line);
		prj.Perform(x);
		pPts.push_back(prj.NearestPoint());
	}
	std::vector<Pnt3d> crackPts;
	for (size_t i = 0; i < thePnts.size(); i++)
	{
		const auto& P0 = thePnts.at(i);
		const auto& P1 = pPts.at(i);

		auto t = theDs.at(i) / P0.Distance(P1);
		auto pt = P0 + t * (P1 - P0);
		//std::cout << pt << std::endl;
		crackPts.push_back(std::move(pt));
	}
	return std::move(crackPts);
}

Handle(Geom_Curve) 
tnbLib::Tools::Interpolate(const std::vector<Pnt3d>& thePnts)
{
	auto pnts = new TColgp_HArray1OfPnt(1, thePnts.size());
	for (size_t i = 0; i < thePnts.size(); i++)
	{
		pnts->SetValue(i + 1, thePnts.at(i));
	}
	GeomAPI_Interpolate alg(pnts, Standard_False, 1.0E-5);
	alg.Perform();
	return alg.Curve();
}

std::tuple<TopoDS_Face, TopoDS_Face, TopoDS_Face>
tnbLib::Tools::CreateTrimSurf
(
	const std::vector<Pnt2d>& thePnts,
	const Standard_Real theWidth, 
	const TopoDS_Face& theFace
)
{
	Dir2d u(thePnts.at(0), thePnts.at(thePnts.size() - 1));
	auto t_left = u.Rotated(PI / 2.0);
	auto t_right = u.Rotated(-PI / 2.0);

	Pnt2d P1 = thePnts.at(0);
	Pnt2d P4 = thePnts.at(thePnts.size() - 1);

	Pnt2d dp(t_right.X() * theWidth, t_right.Y() * theWidth);
	auto P0 = P1 - dp;
	auto P2 = P1 + dp;
	auto P5 = P4 - dp;
	auto P3 = P4 + dp;

	auto theSurf = BRep_Tool::Surface(theFace);

	TopoDS_Face S0, S1, S2;
	{
		auto c0 = Pln_CurveTools::MakeSegment(P0, P1);
		auto c1 = Pln_CurveTools::MakeSegment(P1, P4);
		auto c2 = Pln_CurveTools::MakeSegment(P4, P5);
		auto c3 = Pln_CurveTools::MakeSegment(P5, P0);

		BRepBuilderAPI_MakeWire wire;
		wire.Add(BRepBuilderAPI_MakeEdge(c0, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c1, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c2, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c3, theSurf));

		BRepLib::BuildCurves3d(wire);

		BRepBuilderAPI_MakeFace face(theSurf, wire);
		S0 = face.Face();
	}
	{
		auto c0 = Pln_CurveTools::MakeSegment(P1, P2);
		auto c1 = Pln_CurveTools::MakeSegment(P2, P3);
		auto c2 = Pln_CurveTools::MakeSegment(P3, P4);
		auto c3 = Pln_CurveTools::MakeSegment(P4, P1);

		BRepBuilderAPI_MakeWire wire;
		wire.Add(BRepBuilderAPI_MakeEdge(c0, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c1, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c2, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c3, theSurf));

		BRepLib::BuildCurves3d(wire);

		BRepBuilderAPI_MakeFace face(theSurf, wire);
		S1 = face.Face();
	}
	{
		auto c0 = Pln_CurveTools::MakeSegment(P0, P5);
		auto c1 = Pln_CurveTools::MakeSegment(P5, P4);
		auto c2 = Pln_CurveTools::MakeSegment(P4, P3);
		auto c3 = Pln_CurveTools::MakeSegment(P3, P2);
		auto c4 = Pln_CurveTools::MakeSegment(P2, P1);
		auto c5 = Pln_CurveTools::MakeSegment(P1, P0);

		BRepBuilderAPI_MakeWire wire;
		wire.Add(BRepBuilderAPI_MakeEdge(c0, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c1, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c2, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c3, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c4, theSurf));
		wire.Add(BRepBuilderAPI_MakeEdge(c5, theSurf));

		BRepLib::BuildCurves3d(wire);

		BRepBuilderAPI_MakeFace face(theFace);
		face.Add(wire);
		S2 = face.Face();
	}
	auto t = std::make_tuple(std::move(S0), std::move(S1), std::move(S2));
	return std::move(t);
}

std::tuple<TopoDS_Face, TopoDS_Face, std::pair<Handle(Geom_Curve), Handle(Geom_Curve)>, std::pair<Handle(Geom_Curve), Handle(Geom_Curve)>>
tnbLib::Tools::CreateCrackSurface
(
	const Handle(Geom_Curve)& theOuter, 
	const Handle(Geom_Curve)& theInner, 
	const Handle(Geom2d_Curve)& theCrack,
	const Handle(Geom_Surface)& thePlane
)
{
	auto outer2d = 
		GeomProjLib::Curve2d(theOuter, thePlane);
	if (NOT outer2d)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane." << endl
			<< abort(FatalError);
	}
	auto inner2d =
		GeomProjLib::Curve2d(theInner, thePlane);
	if (NOT inner2d)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane." << endl
			<< abort(FatalError);
	}
	Handle(Geom_Curve) C3d0_upper;
	Handle(Geom_Curve) C3d0_lower;
	TopoDS_Face S0, S1;
	{ // surface S0 [5/1/2023 Payvand]
		auto P0 = theCrack->Value(theCrack->LastParameter());
		auto P1 = inner2d->Value(inner2d->LastParameter());
		std::cout << "P0: " << P0 << std::endl;
		std::cout << "P1: " << P1 << std::endl;
		std::cout << "P03d: " << thePlane->Value(P0.X(), P0.Y()) << std::endl;
		std::cout << "P13d: " << thePlane->Value(P1.X(), P1.Y()) << std::endl;
		auto upper = Pln_CurveTools::MakeSegment(P0, P1);

		auto P2 = inner2d->Value(inner2d->FirstParameter());
		auto P3 = theCrack->Value(theCrack->FirstParameter());
		/*std::cout << "P2: " << P2 << std::endl;
		std::cout << "P3: " << P3 << std::endl;
		std::cout << "P23d: " << thePlane->Value(P2.X(), P2.Y()) << std::endl;
		std::cout << "P33d: " << thePlane->Value(P3.X(), P3.Y()) << std::endl;*/
		auto lower = Pln_CurveTools::MakeSegment(P2, P3);

		BRepBuilderAPI_MakeWire wire;
		wire.Add(BRepBuilderAPI_MakeEdge(theCrack, thePlane));
		wire.Add(BRepBuilderAPI_MakeEdge(upper, thePlane));
		wire.Add(BRepBuilderAPI_MakeEdge(inner2d, thePlane));
		wire.Add(BRepBuilderAPI_MakeEdge(lower, thePlane));
		std::cout << "injaaaaaa" << std::endl;
		BRepLib::BuildCurves3d(wire);

		BRepBuilderAPI_MakeFace face(thePlane, wire);
		S0 = face;

		auto P03d = thePlane->Value(P0.X(), P0.Y());
		auto P13d = thePlane->Value(P1.X(), P1.Y());
		GC_MakeSegment maker(P03d, P13d);
		C3d0_upper = maker.Value();

		auto P23d = thePlane->Value(P2.X(), P2.Y());
		auto P33d = thePlane->Value(P3.X(), P3.Y());

		GC_MakeSegment maker1(P23d, P33d);
		C3d0_lower = maker1.Value();

	}
	PAUSE;
	Handle(Geom_Curve) C3d1_upper;
	Handle(Geom_Curve) C3d1_lower;
	{// surface S1 [5/1/2023 Payvand]
		auto P0 = outer2d->Value(outer2d->LastParameter());
		auto P1 = theCrack->Value(theCrack->LastParameter());
		std::cout << "P0: " << P0 << std::endl;
		std::cout << "P1: " << P1 << std::endl;
		std::cout << "P03d: " << thePlane->Value(P0.X(), P0.Y()) << std::endl;
		std::cout << "P13d: " << thePlane->Value(P1.X(), P1.Y()) << std::endl;
		{
			auto P2 = theCrack->Value(theCrack->FirstParameter());
			auto P3 = outer2d->Value(outer2d->FirstParameter());
			std::cout << "P2: " << P2 << std::endl;
			std::cout << "P3: " << P3 << std::endl;
			std::cout << "P23d: " << thePlane->Value(P2.X(), P2.Y()) << std::endl;
			std::cout << "P33d: " << thePlane->Value(P3.X(), P3.Y()) << std::endl;
		}

		auto upper = Pln_CurveTools::MakeSegment(P0, P1);

		auto P2 = theCrack->Value(theCrack->FirstParameter());
		auto P3 = outer2d->Value(outer2d->FirstParameter());

		auto lower = Pln_CurveTools::MakeSegment(P2, P3);

		BRepBuilderAPI_MakeWire wire;
		wire.Add(BRepBuilderAPI_MakeEdge(outer2d, thePlane));
		wire.Add(BRepBuilderAPI_MakeEdge(upper, thePlane));
		wire.Add(BRepBuilderAPI_MakeEdge(theCrack, thePlane));
		wire.Add(BRepBuilderAPI_MakeEdge(lower, thePlane));
		std::cout << "injaaaaaa" << std::endl;
		BRepLib::BuildCurves3d(wire);
		std::cout << "injaaaaaa" << std::endl;
		BRepBuilderAPI_MakeFace face(thePlane, wire);
		S1 = face.Face();

		auto P03d = thePlane->Value(P0.X(), P0.Y());
		auto P13d = thePlane->Value(P1.X(), P1.Y());
		GC_MakeSegment maker(P03d, P13d);
		C3d1_upper = maker.Value();

		auto P23d = thePlane->Value(P2.X(), P2.Y());
		auto P33d = thePlane->Value(P3.X(), P3.Y());

		GC_MakeSegment maker1(P23d, P33d);
		C3d1_lower = maker1.Value();
	}
	PAUSE;
	auto paired1 = std::make_pair(std::move(C3d0_upper), std::move(C3d1_upper));
	auto paired2 = std::make_pair(std::move(C3d0_lower), std::move(C3d1_lower));
	auto t = std::make_tuple(std::move(S0), std::move(S1), std::move(paired1), std::move(paired2));
	return std::move(t);
}

TopoDS_Face 
tnbLib::Tools::CreateSidePlane
(
	const Handle(Geom_Curve)& theOuter, 
	const Handle(Geom_Curve)& theInner,
	const Handle(Geom_Surface)& thePlane
)
{
	auto outer2d =
		GeomProjLib::Curve2d(theOuter, thePlane);
	if (NOT outer2d)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane." << endl
			<< abort(FatalError);
	}
	auto inner2d =
		GeomProjLib::Curve2d(theInner, thePlane);
	if (NOT inner2d)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane." << endl
			<< abort(FatalError);
	}

	auto P0 = outer2d->Value(outer2d->LastParameter());
	auto P1 = inner2d->Value(inner2d->LastParameter());

	auto upper = Pln_CurveTools::MakeSegment(P0, P1);

	auto P3 = inner2d->Value(inner2d->FirstParameter());
	auto P4 = outer2d->Value(outer2d->FirstParameter());

	auto lower = Pln_CurveTools::MakeSegment(P3, P4);

	BRepBuilderAPI_MakeWire wire;
	wire.Add(BRepBuilderAPI_MakeEdge(outer2d, thePlane));
	wire.Add(BRepBuilderAPI_MakeEdge(upper, thePlane));
	wire.Add(BRepBuilderAPI_MakeEdge(inner2d, thePlane));
	wire.Add(BRepBuilderAPI_MakeEdge(lower, thePlane));

	BRepLib::BuildCurves3d(wire);

	BRepBuilderAPI_MakeFace face(thePlane, wire);
	return face.Face();
}

std::vector<Handle(Geom_Curve)> 
tnbLib::Tools::OuterBoundaryCurves(const TopoDS_Face& theFace)
{
	auto wire = BRepTools::OuterWire(theFace);
	std::vector<Handle(Geom_Curve)> curves;
	for (
		BRepTools_WireExplorer anEdgeExp(wire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		auto edge = TopoDS::Edge(anEdgeExp.Current());
		Standard_Real f, l;
		auto curve = BRep_Tool::Curve(edge, f, l);
		Handle(Geom_Curve) t = new Geom_TrimmedCurve(curve, f, l);
		curves.push_back(std::move(t));
	}
	return std::move(curves);
}