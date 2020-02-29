//#include <Marine_Launch.hxx>
//
//#include <Entity3d_Box.hxx>
//#include <Marine_CrossSection.hxx>
//#include <Marine_CmpSection.hxx>
//#include <Marine_Section.hxx>
//#include <Marine_DrySection.hxx>
//#include <Marine_WetSection.hxx>
//#include <Marine_Wave.hxx>
//#include <Marine_Launch_Info.hxx>
//#include <Pln_Wire.hxx>
//#include <Pln_Tools.hxx>
//#include <Cad_Tools.hxx>
//#include <Cad2d_Plane.hxx>
//#include <Cad2d_Boolean.hxx>
//#include <error.hxx>
//#include <OSstream.hxx>
//
//#include <gp_Ax2.hxx>
//#include <gp_Dir.hxx>
//#include <gp_Pln.hxx>
//#include <Standard_Handle.hxx>
//#include <Geom_BSplineCurve.hxx>
//#include <Geom_Line.hxx>
//#include <Geom_Plane.hxx>
//#include <Geom_TrimmedCurve.hxx>
//#include <GeomAPI_ProjectPointOnCurve.hxx>
//#include <GeomProjLib.hxx>
//#include <BRepAlgoAPI_Section.hxx>
//#include <BRep_Tool.hxx>
//#include <TopoDS.hxx>
//#include <TopoDS_Edge.hxx>
//#include <TopExp_Explorer.hxx>
//
//namespace tnbLib
//{
//
//	namespace launchLib
//	{
//
//		static Handle(Geom_Curve)
//			CreateLine
//			(
//				const Pnt3d& theP0,
//				const Pnt3d& theP1
//			)
//		{
//			gp_Vec v(theP0, theP1);
//			Handle(Geom_Curve) c = new Geom_Line(theP0, gp_Dir(v));
//
//			GeomAPI_ProjectPointOnCurve proj;
//			proj.Init(theP0, c);
//
//			const auto u0 = proj.LowerDistanceParameter();
//
//			proj.Init(theP1, c);
//
//			const auto u1 = proj.LowerDistanceParameter();
//
//			auto trimmed = Cad_Tools::ConvertToTrimmed(c, u0, u1);
//			return std::move(trimmed);
//		}
//
//		static std::shared_ptr<Pln_Wire> 
//			WaterArea
//			(
//				const Handle(Geom_Curve)& theCurve, 
//				const gp_Ax2& theSystem,
//				const Standard_Real theZmin,
//				const Standard_Real theMinTol,
//				const Standard_Real theMaxTol
//			)
//		{
//			Pnt3d leftPt;
//			Pnt3d rightPt;
//
//			auto p0 = theCurve->Value(theCurve->FirstParameter());
//			auto p1 = theCurve->Value(theCurve->LastParameter());
//
//			if (p0.Y() < p1.Y())
//			{
//				leftPt = p0;
//				rightPt = p1;
//			}
//			else
//			{
//				leftPt = p1;
//				rightPt = p0;
//			}
//
//			auto p2 = leftPt + (theZmin - leftPt.Z()) * Pnt3d(theSystem.YDirection().XYZ());
//			auto p3 = rightPt - (theZmin - rightPt.Z()) * Pnt3d(theSystem.YDirection().XYZ());
//
//			auto c0 = CreateLine(leftPt, p2);
//			auto c1 = CreateLine(p2, p3);
//			auto c2 = CreateLine(p3, rightPt);
//
//			gp_Pln plane(theSystem);
//			Handle(Geom_Plane) g = new Geom_Plane(plane);
//
//			auto cprj0 = GeomProjLib::ProjectOnPlane(c0, g, theSystem.Direction(), Standard_True);
//			auto cprj1 = GeomProjLib::ProjectOnPlane(c1, g, theSystem.Direction(), Standard_True);
//			auto cprj2 = GeomProjLib::ProjectOnPlane(c2, g, theSystem.Direction(), Standard_True);
//			auto cprj3 = GeomProjLib::ProjectOnPlane(theCurve, g, theSystem.Direction(), Standard_True);
//
//			auto c2d0 = GeomProjLib::Curve2d(cprj0, g);
//			if (NOT c2d0)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "unable to project the curve on the plane!" << endl
//					<< abort(FatalError);
//			}
//
//			auto c2d1 = GeomProjLib::Curve2d(cprj1, g);
//			if (NOT c2d1)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "unable to project the curve on the plane!" << endl
//					<< abort(FatalError);
//			}
//
//			auto c2d2 = GeomProjLib::Curve2d(cprj2, g);
//			if (NOT c2d2)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "unable to project the curve on the plane!" << endl
//					<< abort(FatalError);
//			}
//
//			auto c2d3 = GeomProjLib::Curve2d(cprj3, g);
//			if (NOT c2d3)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "unable to project the curve on the plane!" << endl
//					<< abort(FatalError);
//			}
//
//			std::vector<Handle(Geom2d_Curve)> curves;
//			curves.push_back(c2d0);
//			curves.push_back(c2d1);
//			curves.push_back(c2d2);
//			curves.push_back(c2d3);
//
//			auto cmpSection = 
//				Marine_CmpSection::CreateCmpSection(curves, theSystem, theMinTol, theMaxTol);
//			Debug_Null_Pointer(cmpSection);
//
//			if (cmpSection->NbSections() NOT_EQUAL 1)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "contradictory data" << endl
//					<< abort(FatalError);
//			}
//
//			auto wire = cmpSection->Sections()[0]->Wire();
//			Debug_Null_Pointer(wire);
//
//			return std::move(wire);
//		}
//
//		static std::tuple
//			<
//			std::shared_ptr<Marine_Section>, 
//			std::shared_ptr<Marine_Section>
//			>
//			CreateSection
//			(
//				const std::shared_ptr<Pln_Wire>& theSection, 
//				const std::shared_ptr<Pln_Wire>& theWater
//			)
//		{
//			auto section = Cad2d_Plane::MakePlane(theSection, nullptr);
//			Debug_Null_Pointer(section);
//
//			auto water = Cad2d_Plane::MakePlane(theWater, nullptr);
//			Debug_Null_Pointer(water);
//
//			auto intsct = Cad2d_Boolean::Intersection(section, water);
//
//			std::shared_ptr<Marine_Section> s_wet = nullptr;
//			std::shared_ptr<Marine_Section> s_dry = nullptr;
//			if (intsct)
//			{
//				if (intsct IS_EQUAL section)
//				{
//					Debug_Null_Pointer(intsct->OuterWire());
//
//					auto wet = std::make_shared<Marine_WetSection>(intsct->OuterWire());
//					Debug_Null_Pointer(wet);
//
//					wet->SetDeep(Standard_True);
//
//					s_wet = std::move(wet);
//					s_dry = nullptr;
//
//					auto t = std::make_tuple(s_wet, s_dry);
//					return std::move(t);
//				}
//				else
//				{
//					Debug_Null_Pointer(intsct->OuterWire());
//
//					auto wet = std::make_shared<Marine_WetSection>(intsct->OuterWire());
//					Debug_Null_Pointer(wet);
//
//					wet->SetDeep(Standard_False);
//
//					s_wet = std::move(wet);
//				}
//			}
//
//			auto subt = Cad2d_Boolean::Subtract(section, water);
//			if (subt)
//			{
//				Debug_Null_Pointer(subt->OuterWire());
//
//				auto dry = std::make_shared<Marine_DrySection>(subt->OuterWire());
//				Debug_Null_Pointer(dry);
//
//				s_dry = std::move(dry);
//				auto t = std::make_tuple(s_wet, s_dry);
//				return std::move(t);
//			}
//		}
//
//		static std::shared_ptr<Marine_CmpSection>
//			RetriveLaunchSection
//			(
//				const std::shared_ptr<Marine_CmpSection>& theSection,
//				const std::shared_ptr<Pln_Wire>& theWater
//			)
//		{
//			auto cmpSection = std::make_shared<Marine_CmpSection>(theSection->Index(), theSection->Name());
//			Debug_Null_Pointer(cmpSection);
//
//			auto& sections = cmpSection->ChangeSections();
//			for (const auto& x : theSection->Sections())
//			{
//				Debug_Null_Pointer(x);
//				
//				auto [wet, dry] = CreateSection(x->Wire(), theWater);
//
//				if (wet)
//				{
//					sections.push_back(std::move(wet));
//				}
//
//				if (dry)
//				{
//					sections.push_back(std::move(dry));
//				}
//			}
//			return std::move(cmpSection);
//		}
//
//		static Handle(Geom_Curve) 
//			WaterLine
//			(
//				const Handle(Geom_Surface)& theSurface,
//				const gp_Ax2& theSystem
//			)
//		{
//			gp_Pln plane(theSystem);
//
//			BRepAlgoAPI_Section alg;
//			alg.SetRunParallel(Standard_True);
//			alg.Init1(plane);
//			alg.Init2(theSurface);
//
//			alg.Build();
//
//			if (alg.Shape().IsNull())
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "Failed to calculate intersection" << endl
//					<< abort(FatalError);
//			}
//
//			auto edges = Marine_CmpSection::RetrieveEdges(alg.Shape());
//			if (edges.size() NOT_EQUAL 1)
//			{
//				FatalErrorIn(FunctionSIG)
//					<< "Contradictory data" << endl
//					<< abort(FatalError);
//			}
//
//			Standard_Real f, l;
//			auto curve = BRep_Tool::Curve(edges[0], f, l);
//			Debug_Null_Pointer(curve);
//
//			if (NOT Handle(Geom_TrimmedCurve)::DownCast(curve))
//			{
//				curve = new Geom_TrimmedCurve(curve, f, l);
//			}
//
//			return std::move(curve);
//		}
//	}
//}
//
//void tnbLib::Marine_Launch::Perform()
//{
//	if (NOT Hull())
//	{
//		FatalErrorIn("void Marine_Launch::Perform()")
//			<< "no hull is loaded!" << endl
//			<< abort(FatalError);
//	}
//
//	if (NOT Wave())
//	{
//		FatalErrorIn("void Marine_Launch::Perform()")
//			<< "no wave is loaded!" << endl
//			<< abort(FatalError);
//	}
//
//	const auto& d = Domain();
//	const auto& waterSurface = Wave()->SurfaceGeometry();
//	if (NOT waterSurface)
//	{
//		FatalErrorIn("void tnbLib::Marine_Launch::Perform()")
//			<< "no geometry is found for water surface" << endl
//			<< abort(FatalError);
//	}
//
//	const auto zmin = d.P0().Z();
//	auto& sections = ChangeSections();
//	auto& waters = ChangeWaters();
//
//	Standard_Integer K = 0;
//	for (const auto& x : Hull()->Sections())
//	{
//		Debug_Null_Pointer(x);
//
//		auto wl = launchLib::WaterLine(waterSurface, x->CoordinateSystem());
//		Debug_Null_Pointer(wl);
//
//		auto wa = launchLib::WaterArea(wl, x->CoordinateSystem(), zmin, Info()->MinTol(), Info()->MaxTol());
//		Debug_Null_Pointer(wa);
//
//		waters.push_back(std::make_shared<Marine_Section>(++K, wa));
//
//		auto section = launchLib::RetriveLaunchSection(x, wa);
//		Debug_Null_Pointer(section);
//
//		sections.push_back(std::move(section));
//	}
//
//	Change_IsDone() = Standard_True;
//}