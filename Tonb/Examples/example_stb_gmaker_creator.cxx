#include <Tnb_Examples.hxx>

#include <Dir3d.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_Tools.hxx>
#include <Geo_UniDistb.hxx>
#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <StbGMaker_ShapeTools.hxx>
#include <StbGMaker_Creator.hxx>
#include <StbGMaker_HullCreator.hxx>
#include <StbGMaker_TankCreator.hxx>
#include <StbGMaker_SailCreator.hxx>
#include <StbGMaker_WP.hxx>
#include <Cad2d_Modeler.hxx>
#include <LegModel_DispNo1.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Bnd_Box.hxx>

namespace tnbLib
{

	void Plot(const std::map<Standard_Integer, std::shared_ptr<StbGMaker_WP>>& WpMap, OFstream& myFile)
	{
		auto info = std::make_shared<Geo_ApprxCurve_Info>();
		Debug_Null_Pointer(info);

		info->SetApprox(1.0e-2);
		info->SetAngle(15);

		for (const auto& x : WpMap)
		{
			Debug_Null_Pointer(x.second);
			const auto& wp = x.second;
			Debug_Null_Pointer(wp);

			const auto& modeler = x.second->Modeler();
			Debug_Null_Pointer(modeler);

			for (const auto& edge : modeler->Edges())
			{
				Debug_Null_Pointer(edge.second);
				const auto& mesh = edge.second->Mesh();

				if (NOT mesh)
				{
					edge.second->Approx(info);
				}

				wp->Approx(edge.second);
			}

			auto mesh3 = wp->MakeMesh();

			if (mesh3)
			{
				mesh3->ExportToPlt(myFile);
			}
		}
	}
}

void tnbLib::example_stb_gmaker_creator()
{
	auto ship = std::make_shared<LegModel_DispNo1>();
	Debug_Null_Pointer(ship);

	ship->Perform();

	const auto& hullShape = ship->Entity();


	gp_Ax2 cyl_ax1(Pnt3d(50, 5, 10), Dir3d(1, 0, 0));
	gp_Ax2 cyl_ax2(Pnt3d(50, -5, 10), Dir3d(1, 0, 0));

	auto cyl1 = Cad_ShapeTools::Cylinder(cyl_ax1, 2, 12.5);
	auto cyl2 = Cad_ShapeTools::Cylinder(cyl_ax2, 2, 12.5);

	auto superShape = Cad_ShapeTools::Box(Pnt3d(10, -7.5, 18), Pnt3d(65, 7.5, 32));

	auto hull = StbGMaker_ShapeTools::Hull(hullShape);
	Debug_Null_Pointer(hull);

	auto tank1 = StbGMaker_ShapeTools::Tank(cyl1);
	Debug_Null_Pointer(tank1);

	auto tank2 = StbGMaker_ShapeTools::Tank(cyl2);
	Debug_Null_Pointer(tank2);

	auto super = StbGMaker_ShapeTools::Sail(superShape);
	Debug_Null_Pointer(super);

	auto bBox_cyl = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(cyl1));
	auto cyl_xDis = std::make_shared<Geo_UniDistb>(20);
	Debug_Null_Pointer(cyl_xDis);

	const auto cyl_tol = bBox_cyl.Diameter()*1.0E-4;
	cyl_xDis->SetLower(bBox_cyl.P0().X() + cyl_tol);
	cyl_xDis->SetUpper(bBox_cyl.P1().X() - cyl_tol);
	cyl_xDis->Perform();

	Debug_If_Condition(NOT cyl_xDis->IsDone());

	auto bBox_super = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(superShape));
	auto sup_xDis = std::make_shared<Geo_UniDistb>(35);
	Debug_Null_Pointer(sup_xDis);

	const auto sup_tol = bBox_super.Diameter()*1.0e-4;
	sup_xDis->SetLower(bBox_super.P0().X() + sup_tol);
	sup_xDis->SetUpper(bBox_super.P1().X() - sup_tol);
	sup_xDis->Perform();

	Debug_If_Condition(NOT sup_xDis->IsDone());

	auto creator = std::make_shared<StbGMaker_Creator>();
	Debug_Null_Pointer(creator);

	const auto sup_id = creator->CreateSailMaker(super);

	const auto& sup_creator = creator->SelectSailMaker(sup_id);
	Debug_Null_Pointer(sup_creator);

	sup_creator->CreateWorkingPlanes(*sup_xDis);

	const auto tank1_id = creator->CreateTankMaker(tank1);
	const auto tank2_id = creator->CreateTankMaker(tank2);

	const auto& tank1_creator = creator->SelectTankMaker(tank1_id);
	Debug_Null_Pointer(tank1_creator);

	const auto& tank2_creator = creator->SelectTankMaker(tank2_id);
	Debug_Null_Pointer(tank2_creator);

	tank1_creator->CreateWorkingPlanes(*cyl_xDis);
	tank2_creator->CreateWorkingPlanes(*cyl_xDis);

	creator->CreateHullMaker(hull);
	
	const auto& hullCreator = creator->HullMaker();
	
	auto bBox = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(hullShape));
	auto xDis = std::make_shared<Geo_UniDistb>(20);
	Debug_Null_Pointer(xDis);

	const auto tol = bBox.Diameter()*1.0E-4;
	xDis->SetLower(bBox.P0().X() + tol);
	xDis->SetUpper(bBox.P1().X() - tol);
	xDis->Perform();

	Debug_If_Condition(NOT xDis->IsDone());
	hullCreator->CreateWorkingPlanes(*xDis);

	fileName myFileName("example_stb_gmaker_creator.plt");
	OFstream myFile(myFileName);

	Plot(hullCreator->WorkingPlanes(), myFile);
	Plot(tank1_creator->WorkingPlanes(), myFile);
	Plot(tank2_creator->WorkingPlanes(), myFile);
	Plot(sup_creator->WorkingPlanes(), myFile);
}