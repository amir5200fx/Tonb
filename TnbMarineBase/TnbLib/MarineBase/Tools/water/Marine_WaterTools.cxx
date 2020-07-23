#include <Marine_WaterTools.hxx>

#include <Pnt3d.hxx>
#include <Entity3d_Box.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Marine_Wave.hxx>
#include <Marine_WaterCurve.hxx>
#include <Marine_Sections.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_SectTools.hxx>

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <GeomProjLib.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	namespace waterLib
	{

		static Handle(Geom_Curve)
			CreateLine
			(
				const Pnt3d& theP0,
				const Pnt3d& theP1
			)
		{
			gp_Vec v(theP0, theP1);
			Handle(Geom_Curve) c = new Geom_Line(theP0, gp_Dir(v));

			GeomAPI_ProjectPointOnCurve proj;
			proj.Init(theP0, c);

			const auto u0 = proj.LowerDistanceParameter();

			proj.Init(theP1, c);

			const auto u1 = proj.LowerDistanceParameter();

			auto trimmed = Cad_Tools::ConvertToTrimmed(c, u0, u1);
			return std::move(trimmed);
		}

		static Handle(Geom_Curve)
			WaterLine
			(
				const Handle(Geom_Surface)& theSurface,
				const gp_Ax2& theSystem
			)
		{
			gp_Pln plane(theSystem);

			BRepAlgoAPI_Section alg;
			alg.SetRunParallel(Standard_True);
			alg.Init1(plane);
			alg.Init2(theSurface);

			alg.Build();

			if (alg.Shape().IsNull())
			{
				FatalErrorIn(FunctionSIG)
					<< "Failed to calculate intersection" << endl
					<< abort(FatalError);
			}

			auto edges = Marine_CmpSection::RetrieveEdges(alg.Shape());
			if (edges.size() NOT_EQUAL 1)
			{
				FatalErrorIn(FunctionSIG)
					<< "Contradictory data" << endl
					<< abort(FatalError);
			}

			Standard_Real f, l;
			auto curve = BRep_Tool::Curve(edges[0], f, l);
			Debug_Null_Pointer(curve);

			if (NOT Handle(Geom_TrimmedCurve)::DownCast(curve))
			{
				curve = new Geom_TrimmedCurve(curve, f, l);
			}

			return std::move(curve);
		}
	}
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Marine_WaterTools::WaterSection
(
	const Handle(Geom_Curve)& theCurve, 
	const gp_Ax2 & theSystem,
	const Standard_Real theZmin, 
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	Pnt3d leftPt;
	Pnt3d rightPt;

	auto p0 = theCurve->Value(theCurve->FirstParameter());
	auto p1 = theCurve->Value(theCurve->LastParameter());

	if (p0.Y() < p1.Y())
	{
		leftPt = p0;
		rightPt = p1;
	}
	else
	{
		leftPt = p1;
		rightPt = p0;
	}

	auto p2 = leftPt + (theZmin - leftPt.Z()) * Pnt3d(theSystem.YDirection().XYZ());
	auto p3 = rightPt + (theZmin - rightPt.Z()) * Pnt3d(theSystem.YDirection().XYZ());

	auto c0 = waterLib::CreateLine(leftPt, p2);
	auto c1 = waterLib::CreateLine(p2, p3);
	auto c2 = waterLib::CreateLine(p3, rightPt);

	gp_Pln plane(theSystem);
	Handle(Geom_Plane) g = new Geom_Plane(plane);

	auto cprj0 = GeomProjLib::ProjectOnPlane(c0, g, theSystem.Direction(), Standard_True);
	auto cprj1 = GeomProjLib::ProjectOnPlane(c1, g, theSystem.Direction(), Standard_True);
	auto cprj2 = GeomProjLib::ProjectOnPlane(c2, g, theSystem.Direction(), Standard_True);
	auto cprj3 = GeomProjLib::ProjectOnPlane(theCurve, g, theSystem.Direction(), Standard_True);

	auto c2d0 = GeomProjLib::Curve2d(cprj0, g);
	if (NOT c2d0)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane!" << endl
			<< abort(FatalError);
	}

	auto c2d1 = GeomProjLib::Curve2d(cprj1, g);
	if (NOT c2d1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane!" << endl
			<< abort(FatalError);
	}

	auto c2d2 = GeomProjLib::Curve2d(cprj2, g);
	if (NOT c2d2)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane!" << endl
			<< abort(FatalError);
	}

	auto c2d3 = GeomProjLib::Curve2d(cprj3, g);
	if (NOT c2d3)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to project the curve on the plane!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.push_back(std::make_shared<Marine_WaterCurve>(1, c2d0));
	curves.push_back(std::make_shared<Marine_WaterCurve>(2, c2d1));
	curves.push_back(std::make_shared<Marine_WaterCurve>(3, c2d2));
	curves.push_back(std::make_shared<Marine_WaterCurve>(4, c2d3));

	auto wires = Pln_Tools::RetrieveWires(curves, theMinTol, theMaxTol);
	if (wires.size() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to detect the wire!" << endl
			<< abort(FatalError);
	}
	return std::move(wires[0]);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_WaterTools::WaterSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody, 
	const Marine_Wave & theWave, 
	const Entity3d_Box & theDomain, 
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	const auto zmin = theDomain.P0().Z();
	const auto& waterSurface = theWave.SurfaceGeometry();
	if (NOT waterSurface)
	{
		FatalErrorIn("std::vector<std::shared_ptr<Marine_Section>> Marine_WaterLib::WaterSections(Args...)")
			<< "no geometry is found for water surface" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Marine_Section>> waters;
	Standard_Integer K = 0;
	for (const auto& x : theBody)
	{
		Debug_Null_Pointer(x);

		auto wl = waterLib::WaterLine(waterSurface, x->CoordinateSystem());
		Debug_Null_Pointer(wl);

		auto wa = WaterSection(wl, x->CoordinateSystem(), zmin, theMinTol, theMaxTol);
		Debug_Null_Pointer(wa);

		auto section = Marine_SectTools::SectionCreator(wa, x->CoordinateSystem(), Marine_SectionType::water);
		Debug_Null_Pointer(section);

		section->SetIndex(++K);
		waters.push_back(std::move(section));
	}
	return std::move(waters);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_WaterTools::StillWaterSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody, 
	const Standard_Real theZ, 
	const Entity3d_Box & theDomain
)
{
	const auto y0 = theDomain.P0().Z();
	const auto y1 = theZ;

	const auto x0 = theDomain.P0().Y();
	const auto x1 = theDomain.P1().Y();

	auto pln = Cad2d_Plane::MakeBox(Pnt2d(x0, y0), Pnt2d(x1, y1));
	Debug_Null_Pointer(pln);

	const auto& wa = pln->OuterWire();
	Debug_Null_Pointer(wa);

	std::vector<std::shared_ptr<Marine_Section>> waters;
	Standard_Integer K = 0;
	for (const auto& x : theBody)
	{
		auto section =
			Marine_SectTools::SectionCreator(wa, x->CoordinateSystem(), Marine_SectionType::water);
		Debug_Null_Pointer(section);

		section->SetIndex(++K);
		waters.push_back(std::move(section));
	}
	return std::move(waters);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_WaterTools::RetrieveNonDeepWLs
(
	const Marine_CmpSection & theSection
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		FatalErrorIn(FunctionSIG)
			<< "the section is not wetted!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Marine_Section>> sections;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);

		auto wetted = Marine_SectTools::WettedSection(x);
		Debug_Null_Pointer(wetted);

		if (NOT wetted->DeepCondition())
		{
			sections.push_back(x);
		}
	}
	return std::move(sections);
}