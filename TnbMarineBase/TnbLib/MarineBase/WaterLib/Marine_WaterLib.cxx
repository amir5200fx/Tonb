#include <Marine_WaterLib.hxx>

#include <Pnt3d.hxx>
#include <Geo_xDistb.hxx>
#include <Entity3d_Box.hxx>
#include <Pln_Curve.hxx>
#include <Cad_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Marine_Wave.hxx>
#include <Marine_WaterCurve.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <Marine_WaterDomain_Still.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterDomains.hxx>
#include <Marine_WettedBody.hxx>
#include <Marine_WetSection.hxx>
#include <error.hxx>
#include <OSstream.hxx>

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

#include <vector>

namespace tnbLib
{

	namespace marineLib
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
tnbLib::Marine_WaterLib::WaterSection
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

	auto c0 = marineLib::CreateLine(leftPt, p2);
	auto c1 = marineLib::CreateLine(p2, p3);
	auto c2 = marineLib::CreateLine(p3, rightPt);

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

	auto cmpSection =
		Marine_xCmpSection::CreateCmpSection(curves, theSystem, theMinTol, theMaxTol);
	Debug_Null_Pointer(cmpSection);

	if (cmpSection->NbSections() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data" << endl
			<< abort(FatalError);
	}

	auto wire = cmpSection->Sections()[0]->Wire();
	Debug_Null_Pointer(wire);

	return std::move(wire);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_WaterLib::WaterSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
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
	for (const auto& x : theModel)
	{
		Debug_Null_Pointer(x);

		auto wl = marineLib::WaterLine(waterSurface, x->CoordinateSystem());
		Debug_Null_Pointer(wl);

		auto wa = WaterSection(wl, x->CoordinateSystem(), zmin, theMinTol, theMaxTol);
		Debug_Null_Pointer(wa);

		auto section = std::make_shared<Marine_Section>(++K, wa);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(x->CoordinateSystem());
		waters.push_back(std::move(section));
	}
	return std::move(waters);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_WaterLib::StillWaterSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
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
	for (const auto& x : theModel)
	{
		auto section = std::make_shared<Marine_Section>(++K, wa);
		Debug_Null_Pointer(section);

		section->SetCoordinateSystem(x->CoordinateSystem());
		waters.push_back(std::move(section));
	}
	return std::move(waters);
}

std::shared_ptr<tnbLib::Marine_WaterDomain> 
tnbLib::Marine_WaterLib::RetrieveStillWaterDomain
(
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
	const Standard_Real theZ
)
{
	auto wd = std::make_shared<Marine_WaterDomain_Still>(theDomain, theZ);
	Debug_Null_Pointer(wd);

	wd->ChangeWaters() = Marine_WaterLib::StillWaterSections(theModel, theZ, theDomain->Dim());
	return std::move(wd);
}

std::shared_ptr<tnbLib::Marine_WaterDomains>
tnbLib::Marine_WaterLib::RetrieveStillWaterDomains
(
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
	const Geo_xDistb & theZ
)
{
	auto domains = std::make_shared<Marine_WaterDomains>();
	Debug_Null_Pointer(domains);

	auto& waters = domains->ChangeDomains();
	waters.reserve(theZ.Size() + 1);
	for (auto z : theZ.Values())
	{
		auto domain = RetrieveStillWaterDomain(theDomain, theModel, z);
		Debug_Null_Pointer(domain);

		waters.push_back(std::move(domain));
	}
	return std::move(domains);
}

std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
tnbLib::Marine_WaterLib::RetrieveWLs
(
	const Marine_CmpSection & theSection
)
{
	std::vector<std::shared_ptr<Marine_Section>> sections;

	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		if (x->IsWetted())
		{
			auto wet = std::dynamic_pointer_cast<Marine_WetSection>(x);
			Debug_Null_Pointer(wet);

			if (NOT wet->DeepCondition())
			{
				sections.push_back(std::move(wet));
			}
		}
	}
	return std::move(sections);
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::FUW
(
	const Marine_WettedBody & theBody
)
{
	const auto& sections = theBody.Sections();
	if (sections.empty())
	{
		FatalErrorIn("const std::shared_ptr<tnbLib::Marine_CmpSection> & FUW()")
			<< "null list" << endl
			<< abort(FatalError);
	}
	return sections[sections.size() - 1];
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::AUW
(
	const Marine_WettedBody & theBody
)
{
	const auto& sections = theBody.Sections();
	if (sections.empty())
	{
		FatalErrorIn("const std::shared_ptr<tnbLib::Marine_CmpSection> & AUW()")
			<< "null list" << endl
			<< abort(FatalError);
	}
	return sections[0];
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::FWL
(
	const Marine_WettedBody & theBody
)
{
	const auto& sections = theBody.Sections();
	for (size_t i = sections.size() - 1; i >= 0; i--)
	{
		const auto& x = sections[i];
		Debug_Null_Pointer(x);

		auto wls = RetrieveWLs(*x);
		if (wls.size())
		{
			return x;
		}
	}
	return Marine_CmpSection::null;
}

const std::shared_ptr<tnbLib::Marine_CmpSection> &
tnbLib::Marine_WaterLib::AWL
(
	const Marine_WettedBody & theBody
)
{
	const auto& sections = theBody.Sections();
	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x);

		auto wls = RetrieveWLs(*x);
		if (wls.size())
		{
			return x;
		}
	}
	return Marine_CmpSection::null;
}