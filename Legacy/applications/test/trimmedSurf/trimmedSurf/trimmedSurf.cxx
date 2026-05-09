#include <Cad_ShapeTools.hxx>
#include <Cad_Shape.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad_Tools.hxx>
#include <Dir3d.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include "Tools.hxx"

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <Message_ProgressRange.hxx>
#include <ShapeFix_Solid.hxx>
#include <ShapeFix_Shape.hxx>
#include <Message_ProgressRange.hxx>
#include <BRepOffsetAPI_MakeFilling.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRep_Builder.hxx>
#include <BRepLib.hxx>
#include <BRepTools.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <gce_MakePln.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Plane.hxx>


using namespace tnbLib;

int main()
{
	// Define the parameters for the cylinder
	gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	Standard_Real outer_rad = 125.0;
	Standard_Real inner_rad = 90;
	Standard_Real height = 250.0;
	Standard_Real width = 0.523;

	// Create the cylindrical surface
	Handle(Geom_Surface) cylinder_surface = new Geom_CylindricalSurface(axis, outer_rad);
	Handle(Geom_Surface) cylinder_surface1 = new Geom_CylindricalSurface(axis, inner_rad);

	Pnt2d P0(0, 0);
	Pnt2d P1(2.0*PI, 0);
	Pnt2d P2(2.0*PI, height);
	Pnt2d P3(0, height);

	auto c0 = Pln_CurveTools::MakeSegment(P0, P1);
	auto c1 = Pln_CurveTools::MakeSegment(P1, P2);
	auto c2 = Pln_CurveTools::MakeSegment(P2, P3);
	auto c3 = Pln_CurveTools::MakeSegment(P3, P0);

	BRepBuilderAPI_MakeWire wire;
	wire.Add(BRepBuilderAPI_MakeEdge(c0, cylinder_surface));
	wire.Add(BRepBuilderAPI_MakeEdge(c1, cylinder_surface));
	wire.Add(BRepBuilderAPI_MakeEdge(c2, cylinder_surface));
	wire.Add(BRepBuilderAPI_MakeEdge(c3, cylinder_surface));

	BRepLib::BuildCurves3d(wire);
	
	BRepBuilderAPI_MakeFace outer_face(cylinder_surface, wire);

	BRepBuilderAPI_MakeWire wire1;
	wire1.Add(BRepBuilderAPI_MakeEdge(c0, cylinder_surface1));
	wire1.Add(BRepBuilderAPI_MakeEdge(c1, cylinder_surface1));
	wire1.Add(BRepBuilderAPI_MakeEdge(c2, cylinder_surface1));
	wire1.Add(BRepBuilderAPI_MakeEdge(c3, cylinder_surface1));

	BRepLib::BuildCurves3d(wire1);

	BRepBuilderAPI_MakeFace inner_face(cylinder_surface1, wire1);


	const Standard_Real Z0 = 50.0;
	std::vector<Standard_Real> Zs;
	//Zs.push_back(0.0);
	//Zs.push_back(1.3516);
	Zs.push_back(3.4194);
	//Zs.push_back(5.2569);
	Zs.push_back(7.354);
	//Zs.push_back(9.7109);
	Zs.push_back(10.3519);
	//Zs.push_back(11.9492);
	Zs.push_back(13.631);
	//Zs.push_back(15.4815);
	Zs.push_back(17.5038);
	//Zs.push_back(18.8916);
	Zs.push_back(21.6623);
	//Zs.push_back(23.4479);
	Zs.push_back(25.9298);
	//Zs.push_back(28.7314);
	Zs.push_back(31.1337);
	//Zs.push_back(34.143);
	Zs.push_back(36.8277);
	//Zs.push_back(39.4862);
	Zs.push_back(42.9923);
	//Zs.push_back(45.2843);
	Zs.push_back(48.2174);
	//Zs.push_back(51.11);
	Zs.push_back(54.2347);
	//Zs.push_back(55.858);
	Zs.push_back(58.5883);
	//Zs.push_back(61.9874);
	Zs.push_back(65);
	//Zs.push_back(66.4135);
	Zs.push_back(69.5381);
	//Zs.push_back(72.5085);
	Zs.push_back(72.525);
	//Zs.push_back(72.5415);
	Zs.push_back(75.5119);
	//Zs.push_back(78.6365);
	Zs.push_back(80.05);
	//Zs.push_back(83.0626);
	Zs.push_back(86.4617);
	//Zs.push_back(89.192);
	Zs.push_back(90.8153);
	//Zs.push_back(93.94);
	Zs.push_back(96.8326);
	//Zs.push_back(99.7657);
	Zs.push_back(102.0577);
	//Zs.push_back(105.5638);
	Zs.push_back(108.2223);
	//Zs.push_back(110.907);
	Zs.push_back(113.9163);
	//Zs.push_back(116.3186);
	Zs.push_back(119.1202);
	//Zs.push_back(121.6021);
	Zs.push_back(123.3877);
	//Zs.push_back(126.1584);
	Zs.push_back(127.5462);
	//Zs.push_back(129.5685);
	Zs.push_back(131.419);
	//Zs.push_back(133.1008);
	Zs.push_back(134.6981);
	//Zs.push_back(135.3391);
	Zs.push_back(137.696);
	//Zs.push_back(139.7931);
	Zs.push_back(141.6306);
	//Zs.push_back(143.6984);
	//Zs.push_back(145.05);


	std::vector<Standard_Real> Ds;
	//Ds.push_back(0);
	//Ds.push_back(2.6389);
	Ds.push_back(3.4986);
	//Ds.push_back(5.7207);
	Ds.push_back(2.5624);
	//Ds.push_back(6.4768);
	Ds.push_back(2.9677);
	//Ds.push_back(6.3368);
	Ds.push_back(5.3895);
	//Ds.push_back(6.6108);
	Ds.push_back(7.1495);
	//Ds.push_back(9.4475);
	Ds.push_back(9.0401);
	//Ds.push_back(10.3879);
	Ds.push_back(10.5219);
	//Ds.push_back(9.5806);
	Ds.push_back(11.0609);
	//Ds.push_back(10.1211);
	Ds.push_back(12.4113);
	//Ds.push_back(10.1172);
	Ds.push_back(13.2225);
	//Ds.push_back(14.3005);
	Ds.push_back(13.2225);
	//Ds.push_back(13.8919);
	Ds.push_back(15.513);
	//Ds.push_back(16.859);
	Ds.push_back(18.8758);
	//Ds.push_back(19.5566);
	Ds.push_back(19.5789);
	//Ds.push_back(19.9558);
	Ds.push_back(19.0242);
	//Ds.push_back(19.4298);
	Ds.push_back(20.5);
	//Ds.push_back(19.4298);
	Ds.push_back(19.0242);
	//Ds.push_back(19.9558);
	Ds.push_back(19.5789);
	//Ds.push_back(19.5566);
	Ds.push_back(18.8758);
	//Ds.push_back(16.859);
	Ds.push_back(15.513);
	//Ds.push_back(13.8919);
	Ds.push_back(13.2225);
	//Ds.push_back(14.3005);
	Ds.push_back(13.2225);
	//Ds.push_back(10.1172);
	Ds.push_back(12.4113);
	//Ds.push_back(10.1211);
	Ds.push_back(11.0609);
	//Ds.push_back(9.5806);
	Ds.push_back(10.5219);
	//Ds.push_back(10.3879);
	Ds.push_back(9.0401);
	//Ds.push_back(9.4475);
	Ds.push_back(7.1495);
	//Ds.push_back(6.6108);
	Ds.push_back(5.3895);
	//Ds.push_back(6.3368);
	Ds.push_back(2.9677);
	//Ds.push_back(6.4768);
	Ds.push_back(2.5624);
	//Ds.push_back(5.7207);
	Ds.push_back(3.4986);
	//Ds.push_back(2.6389);
	//Ds.push_back(0);

	auto Pts3d = Tools::CalcPnt3ds(Z0, Zs, outer_rad, PI);

	auto outer_prj_pts = Tools::ProjectPointsToCylinderSurf(Pts3d, BRep_Tool::Surface(outer_face));
	auto inner_prj_pts = Tools::ProjectPointsToCylinderSurf(Pts3d, BRep_Tool::Surface(inner_face));
	auto crack_pts = Tools::CalcCrackPoints(Pts3d, Ds, gp::OZ());

	auto outer_geom = BRep_Tool::Surface(outer_face);
	auto inner_geom = BRep_Tool::Surface(inner_face);

	Handle(Geom_Surface) crack_pln;
	{// Calculate the geometric plane of the crack [5/1/2023 Payvand]
		auto p2d0 = outer_prj_pts.at(0);
		auto p2d1 = outer_prj_pts.at(outer_prj_pts.size() - 1);
		auto p2d2 = inner_prj_pts.at(0);

		

		auto p3d0 = outer_geom->Value(p2d0.X(), p2d0.Y());
		auto p3d1 = outer_geom->Value(p2d1.X(), p2d1.Y());
		auto p3d2 = inner_geom->Value(p2d2.X(), p2d2.Y());

		//Pnt3d P00(0, 0, 0);
		//Pnt3d P01(1.0, 0, 0);
		//Pnt3d P02(1.0, 1.0, 0);
		Dir3d v0(p3d2, p3d0);
		Dir3d v1(p3d2, p3d1);
		auto n = v0.Crossed(v1);
		gce_MakePln plnMaker(axis.Location(), n);
		//gce_MakePln plnMaker(P00, P01, P02);

		crack_pln = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -10000.0, 10000.0, -10000.0, 10000.0);
	}

	auto [outer_crackside_face_1, outer_crackside_face_2, outer_face_trimmed] = Tools::CreateTrimSurf(outer_prj_pts, width, outer_face);
	auto [inner_crackside_face_1, inner_crackside_face_2, inner_face_trimmed] = Tools::CreateTrimSurf(inner_prj_pts, width, inner_face);

	auto crack_curve = Tools::Interpolate(crack_pts);
	auto outer_crack_curve = Tools::Interpolate(Tools::CalcPnt3ds(outer_prj_pts, outer_geom));
	auto inner_crack_curve = Tools::Interpolate(Tools::CalcPnt3ds(inner_prj_pts, inner_geom));

	auto [inner_side_crack_face, outer_side_crack_face, upper_curves, lower_curves] 
		= Tools::CreateCrackSurface(outer_crack_curve, inner_crack_curve, Tools::ProjectCurveOnSurf(crack_curve,crack_pln), crack_pln);

	Handle(Geom_Surface) side_pln_1;
	TopoDS_Face side_face_1;
	{ // side plane 1 [5/2/2023 Payvand]
		auto curves_1 = Tools::OuterBoundaryCurves(outer_crackside_face_1);
		auto curves_2 = Tools::OuterBoundaryCurves(inner_crackside_face_1);

		const auto& outter_curve = curves_1.at(curves_1.size() - 1);
		const auto& inner_curve = curves_2.at(curves_2.size() - 1);

		auto P3d0 = outter_curve->Value(outter_curve->FirstParameter());
		auto P3d1 = outter_curve->Value(outter_curve->LastParameter());
		auto P3d2 = inner_curve->Value(inner_curve->FirstParameter());

		Dir3d v0(P3d2, P3d0);
		Dir3d v1(P3d2, P3d1);
		auto n = v0.Crossed(v1);
		gce_MakePln plnMaker(axis.Location(), n);

		side_pln_1 = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

		side_face_1 = Tools::CreateSidePlane(outter_curve, inner_curve, side_pln_1);
	}
	
	Handle(Geom_Surface) side_pln_2;
	TopoDS_Face side_face_2;
	{// side plane 2 [5/2/2023 Payvand]
		auto curves_1 = Tools::OuterBoundaryCurves(outer_crackside_face_2);
		auto curves_2 = Tools::OuterBoundaryCurves(inner_crackside_face_2);

		const auto& outter_curve = curves_1.at(1);
		const auto& inner_curve = curves_2.at(1);

		auto P3d0 = outter_curve->Value(outter_curve->FirstParameter());
		auto P3d1 = outter_curve->Value(outter_curve->LastParameter());
		auto P3d2 = inner_curve->Value(inner_curve->FirstParameter());

		Dir3d v0(P3d2, P3d0);
		Dir3d v1(P3d2, P3d1);
		auto n = v0.Crossed(v1);
		gce_MakePln plnMaker(axis.Location(), n);

		side_pln_2 = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

		side_face_2 = Tools::CreateSidePlane(outter_curve, inner_curve, side_pln_2);
		//Cad_Tools::ExportToSTEP(side_face_2, "compound.step");
	}
	
	Handle(Geom_Surface) lower_pln_1;
	TopoDS_Face lower_face_1;
	Handle(Geom_Surface) upper_pln_1;
	TopoDS_Face upper_face_1;
	{// lower plane 1 [5/2/2023 Payvand]
		auto curves_1 = Tools::OuterBoundaryCurves(inner_side_crack_face);
		auto curves_2 = Tools::OuterBoundaryCurves(outer_side_crack_face);

		auto curves_3 = Tools::OuterBoundaryCurves(side_face_1);

		auto curves_4 = Tools::OuterBoundaryCurves(outer_crackside_face_1);
		auto curves_5 = Tools::OuterBoundaryCurves(inner_crackside_face_1);

		{
			// upper side [5/2/2023 Payvand]
			auto c0 = curves_4.at(2);
			auto c1 = curves_3.at(1);
			auto c2 = curves_5.at(2);
			auto c3 = curves_1.at(1);
			auto c4 = curves_2.at(1);

			Pnt3d loc(0, 0, Z0 + Zs.at(Zs.size() - 1));
			gce_MakePln plnMaker(loc, axis.Direction());
			upper_pln_1 = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

			BRepBuilderAPI_MakeWire wire;
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c0, upper_pln_1), upper_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, upper_pln_1), upper_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c2, upper_pln_1), upper_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c3, upper_pln_1), upper_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c4, upper_pln_1), upper_pln_1));

			BRepLib::BuildCurves3d(wire);

			BRepBuilderAPI_MakeFace face(upper_pln_1, wire);
			upper_face_1 = face;
		}

		{
			auto c0 = curves_4.at(0);
			auto c1 = curves_3.at(3);
			auto c2 = curves_5.at(0);
			auto c3 = curves_1.at(3);
			auto c4 = curves_2.at(3);

			Pnt3d loc(0, 0, Z0 + Zs.at(0));
			gce_MakePln plnMaker(loc, axis.Direction());
			lower_pln_1 = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

			BRepBuilderAPI_MakeWire wire;
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c0, lower_pln_1), lower_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, lower_pln_1), lower_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c2, lower_pln_1), lower_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c3, lower_pln_1), lower_pln_1));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c4, lower_pln_1), lower_pln_1));

			BRepLib::BuildCurves3d(wire);

			BRepBuilderAPI_MakeFace face(lower_pln_1, wire);
			lower_face_1 = face;
		}
	}

	Handle(Geom_Surface) lower_pln_2;
	TopoDS_Face lower_face_2;
	Handle(Geom_Surface) upper_pln_2;
	TopoDS_Face upper_face_2;
	{
		auto curves_1 = Tools::OuterBoundaryCurves(inner_side_crack_face);
		auto curves_2 = Tools::OuterBoundaryCurves(outer_side_crack_face);

		auto curves_3 = Tools::OuterBoundaryCurves(side_face_2);

		auto curves_4 = Tools::OuterBoundaryCurves(outer_crackside_face_2);
		auto curves_5 = Tools::OuterBoundaryCurves(inner_crackside_face_2);

		{
			// upper side [5/2/2023 Payvand]
			auto c0 = curves_4.at(2);
			auto c1 = curves_2.at(1);
			auto c2 = curves_1.at(1);
			auto c3 = curves_5.at(2);
			auto c4 = curves_3.at(1);

			Pnt3d loc(0, 0, Z0 + Zs.at(Zs.size() - 1));
			gce_MakePln plnMaker(loc, axis.Direction());
			upper_pln_2 = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

			BRepBuilderAPI_MakeWire wire;
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c0, upper_pln_2), upper_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, upper_pln_2), upper_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c2, upper_pln_2), upper_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c3, upper_pln_2), upper_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c4, upper_pln_2), upper_pln_2));

			BRepLib::BuildCurves3d(wire);

			BRepBuilderAPI_MakeFace face(upper_pln_2, wire);
			upper_face_2 = face;
		}

		{
			auto c0 = curves_4.at(0);
			auto c1 = curves_2.at(3);
			auto c2 = curves_1.at(3);
			auto c3 = curves_5.at(0);
			auto c4 = curves_3.at(3);

			Pnt3d loc(0, 0, Z0 + Zs.at(0));
			gce_MakePln plnMaker(loc, axis.Direction());
			lower_pln_2 = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

			BRepBuilderAPI_MakeWire wire;
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c0, lower_pln_2), lower_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, lower_pln_2), lower_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c2, lower_pln_2), lower_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c3, lower_pln_2), lower_pln_2));
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c4, lower_pln_2), lower_pln_2));

			BRepLib::BuildCurves3d(wire);

			BRepBuilderAPI_MakeFace face(lower_pln_2, wire);
			lower_face_2 = face;
		}
	}

	Handle(Geom_Surface) upper_last_pln;
	Handle(Geom_Surface) lower_last_pln;
	TopoDS_Face upper_last_face;
	TopoDS_Face lower_last_face;
	{
		auto curves_1 = Tools::OuterBoundaryCurves(outer_face);
		auto curves_2 = Tools::OuterBoundaryCurves(inner_face);

		/*for (const auto& x : curves_1)
		{
			std::cout << x->Value(x->FirstParameter()) << ", " << x->Value(x->LastParameter()) << std::endl;
		}*/

		{// lower face [5/2/2023 Payvand]
			Pnt3d loc(0, 0, height/* + Zs.at(Zs.size() - 1)*/);
			gce_MakePln plnMaker(loc, axis.Direction());
			lower_last_pln = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

			auto c0 = curves_1.at(0);
			auto c1 = curves_2.at(0);

			BRepBuilderAPI_MakeWire wire;
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c0, lower_last_pln), lower_last_pln));

			//wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, lower_last_pln), lower_last_pln));

			BRepLib::BuildCurves3d(wire);

			BRepBuilderAPI_MakeFace face(lower_last_pln, wire);

			BRepBuilderAPI_MakeWire inner_wire;
			inner_wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, lower_last_pln)->Reversed(), lower_last_pln));
			
			BRepLib::BuildCurves3d(inner_wire);

			BRepBuilderAPI_MakeFace trimmed_inner(face);
			trimmed_inner.Add(inner_wire);

			lower_last_face = trimmed_inner;
		}

		{// upper face [5/2/2023 Payvand]
			gce_MakePln plnMaker(axis.Location(), axis.Direction());
			upper_last_pln = new Geom_RectangularTrimmedSurface(new Geom_Plane(plnMaker.Value()), -1000.0, 1000.0, -1000.0, 1000.0);

			auto c0 = curves_1.at(2);
			auto c1 = curves_2.at(2);

			BRepBuilderAPI_MakeWire wire;
			wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c0, upper_last_pln), upper_last_pln));

			//wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, upper_last_pln), upper_last_pln));

			BRepLib::BuildCurves3d(wire);

			BRepBuilderAPI_MakeFace face(upper_last_pln, wire);

			BRepBuilderAPI_MakeWire inner_wire;
			inner_wire.Add(BRepBuilderAPI_MakeEdge(Tools::ProjectCurveOnSurf(c1, upper_last_pln), upper_last_pln));

			BRepLib::BuildCurves3d(inner_wire);

			BRepBuilderAPI_MakeFace trimmed_inner(face);
			trimmed_inner.Add(inner_wire);

			upper_last_face = trimmed_inner;
		}
	}

	TopoDS_CompSolid solid_compound;
	TopoDS_Builder solid_builder;
	solid_builder.MakeCompSolid(solid_compound);
	{// create solid S0 [5/2/2023 Payvand]
		TopoDS_Compound compound;
		TopoDS_Builder builder;
		builder.MakeCompound(compound);

		builder.Add(compound, outer_crackside_face_1);	
		builder.Add(compound, inner_crackside_face_1);
		builder.Add(compound, inner_side_crack_face);
		builder.Add(compound, outer_side_crack_face);
		builder.Add(compound, side_face_1);
		builder.Add(compound, upper_face_1);
		builder.Add(compound, lower_face_1);
		
		//Cad_Tools::ExportToSTEP(compound, "compound.step");

		BRepOffsetAPI_Sewing swing;
		swing.Add(compound);
		swing.Perform();

		TopoDS_Shape sewed = swing.SewedShape();
		for (TopExp_Explorer explorer(sewed, TopAbs_SHELL); explorer.More(); explorer.Next())
		{
			TopoDS_Shell shell = TopoDS::Shell(explorer.Current());
			BRepBuilderAPI_MakeSolid brep_solid(shell);
			TopoDS_Solid solid = brep_solid.Solid();

			/*GProp_GProps System;
			BRepGProp::VolumeProperties(solid, System);

			std::cout << System.Mass() << std::endl;*/

			/*Handle(ShapeFix_Shape) aFixShape = new ShapeFix_Shape();
			aFixShape->Init(solid);

			aFixShape->SetPrecision(1.0e-4);
			aFixShape->SetMinTolerance(1.0E-4);
			aFixShape->SetMaxTolerance(1.0E-4);

			aFixShape->Perform();*/

			solid_builder.Add(solid_compound, solid);
		}
	}
	{// create solid s1 [5/2/2023 Payvand]
		TopoDS_Compound compound;
		TopoDS_Builder builder;
		builder.MakeCompound(compound);

		builder.Add(compound, outer_crackside_face_2);
		builder.Add(compound, inner_crackside_face_2);
		builder.Add(compound, inner_side_crack_face);
		builder.Add(compound, outer_side_crack_face);
		builder.Add(compound, side_face_2);
		builder.Add(compound, upper_face_2);
		builder.Add(compound, lower_face_2);

		BRepOffsetAPI_Sewing swing;
		swing.Add(compound);
		swing.Perform();

		TopoDS_Shape sewed = swing.SewedShape();
		for (TopExp_Explorer explorer(sewed, TopAbs_SHELL); explorer.More(); explorer.Next())
		{
			TopoDS_Shell shell = TopoDS::Shell(explorer.Current());
			BRepBuilderAPI_MakeSolid brep_solid(shell);
			TopoDS_Solid solid = brep_solid.Solid();

			/*GProp_GProps System;
			BRepGProp::VolumeProperties(solid, System);

			std::cout << System.Mass() << std::endl;*/

			solid_builder.Add(solid_compound, solid);
		}
	}
	{// create cylinder solid [5/2/2023 Payvand]
		TopoDS_Compound compound;
		TopoDS_Builder builder;
		builder.MakeCompound(compound);

		builder.Add(compound, upper_last_face);
		builder.Add(compound, lower_last_face);
		builder.Add(compound, outer_face_trimmed);
		////builder.Add(compound, inner_crackside_face_1);
		////builder.Add(compound, inner_crackside_face_2);
		builder.Add(compound, inner_face_trimmed);
		builder.Add(compound, side_face_1);
		builder.Add(compound, side_face_2);
		builder.Add(compound, upper_face_1);
		builder.Add(compound, lower_face_1);
		builder.Add(compound, upper_face_2);
		builder.Add(compound, lower_face_2);
		

		/*auto myShape = std::make_shared<Cad_Shape>(compound);
		file::SaveTo(myShape, "cylinder.shape", 1);
		std::exit(1);*/

		BRepOffsetAPI_Sewing swing;
		/*swing.SetMaxTolerance(1.0E-4);
		swing.SetMinTolerance(1.0E-4);
		swing.SetTolerance(1.0E-4);*/
		swing.Add(compound);
		swing.Perform();

		TopoDS_Shape sewed = swing.SewedShape();
		for (TopExp_Explorer explorer(sewed, TopAbs_SHELL); explorer.More(); explorer.Next())
		{
			TopoDS_Shell shell = TopoDS::Shell(explorer.Current());
			BRepBuilderAPI_MakeSolid brep_solid(shell);
			TopoDS_Solid solid = brep_solid.Solid();

			solid.Reverse();

			/*GProp_GProps System;
			BRepGProp::VolumeProperties(solid, System);

			std::cout << System.Mass() << std::endl;*/

			solid_builder.Add(solid_compound, solid);
		}
	}

	/*BRep_Builder builder;
	TopoDS_Compound Comp;
	builder.MakeCompound(Comp);
	builder.Add(Comp, outer_crackside_face_1);
	builder.Add(Comp, outer_crackside_face_2);
	builder.Add(Comp, outer_face_trimmed);
	builder.Add(Comp, inner_crackside_face_1);
	builder.Add(Comp, inner_crackside_face_2);
	builder.Add(Comp, inner_face_trimmed);
	builder.Add(Comp, inner_side_crack_face);
	builder.Add(Comp, outer_side_crack_face);
	builder.Add(Comp, side_face_1);
	builder.Add(Comp, side_face_2);
	builder.Add(Comp, upper_face_1);
	builder.Add(Comp, lower_face_1);
	builder.Add(Comp, upper_face_2);
	builder.Add(Comp, lower_face_2);
	builder.Add(Comp, upper_last_face);
	builder.Add(Comp, lower_last_face);*/

	//Handle(Geom_Surface) myPln = new Geom_RectangularTrimmedSurface(new Geom_Plane(Pnt3d(0, 0, 0), gp::DX()), -6.0, 6.0, -6.0, 6.0);

	//Pnt2d P4(0.0, 0.0);
	//Pnt2d P5(1.0, 0.0);
	//Pnt2d P6(1.0, 1.0);
	//Pnt2d P7(0.0, 1.0);

	//auto c4 = Pln_CurveTools::MakeSegment(P4, P5);
	//auto c5 = Pln_CurveTools::MakeSegment(P5, P6);
	//auto c6 = Pln_CurveTools::MakeSegment(P6, P7);
	//auto c7 = Pln_CurveTools::MakeSegment(P7, P4);

	//BRepBuilderAPI_MakeWire wire2;
	//wire2.Add(BRepBuilderAPI_MakeEdge(c4, myPln));
	//wire2.Add(BRepBuilderAPI_MakeEdge(c5, myPln));
	//wire2.Add(BRepBuilderAPI_MakeEdge(c6, myPln));
	//wire2.Add(BRepBuilderAPI_MakeEdge(c7, myPln));

	//BRepBuilderAPI_MakeFace facexx(myPln, wire2);
	////face.Add(wire1);
	//{
	//	auto ss = BRep_Tool::Surface(facexx);
	//	Standard_Real u0, u1, v0, v1;
	//	ss->Bounds(u0, u1, v0, v1);
	//	std::cout << u0 << ", " << u1 << ", " << v0 << ", " << v1 << std::endl;
	//}
	Cad_Tools::ExportToIGES("m", solid_compound, "cylinder.iges");
	auto myShape = std::make_shared<Cad_Shape>(solid_compound);
	file::SaveTo(myShape, "cylinder.shape", 1);
	//Cad_Tools::ExportToSTEP(solid_compound, "cylinder.step");
	BRepTools::Write(solid_compound, "cylinder.brep");
	return 0;
}