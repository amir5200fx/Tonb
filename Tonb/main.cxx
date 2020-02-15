#include <Standard_TypeDef.hxx>

#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <TnbCad2d_System.hxx>
#include <dimensionedScalar.hxx>

#include <Marine_SectionDistribution_Uniform.hxx>
#include <Marine_ModelMaker_Shape.hxx>
#include <Marine_FlatWave.hxx>
#include <LegModel_DispNo1.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_System.hxx>
#include <FastDiscrete_Params.hxx>

#include <Poly_Triangulation.hxx>
#include <Bnd_Box.hxx>

#include <Tnb_Examples.hxx>

#include <armadillo.h>

using namespace tnbLib;

Standard_Integer main()
{

	example_union_plane_box();

	PAUSE;
	return 0;

	fileName name("out.plt");
	OFstream myFile(name);
	/*sysLib::init_TnbCad2d();

	auto pln = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1.0, 0.38), sysLib::gl_cad2d_plane_info);
	Debug_Null_Pointer(pln);*/

	/*dimensionedScalar dim0("CB", dimless, 0.1);
	dimensionedScalar dim1("CB", dimless, 0.5);

	auto d = dim0*dim0 + dim1;

	myFile << d << endl;*/

	auto ship = std::make_shared<LegModel_DispNo1>();
	Debug_Null_Pointer(ship);

	ship->Perform();

	const auto& myShape = ship->Entity();

	auto b0 = Cad_Tools::BoundingBox(myShape);
	auto box = Cad_Tools::BoundingBox(b0);

	FastDiscrete_Params params;
	params.Deflection = 1.0e-4*box.Diameter();
	params.Angle = 1.0;

	Cad_FastDiscrete::Triangulation(myShape, params);

	auto myTris = Cad_Tools::RetrieveTriangulation(myShape);

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}

	auto domain = box.OffSet(box.Diameter()*0.2);
	auto wave = std::make_shared<Marine_FlatWave>(domain);
	Debug_Null_Pointer(wave);

	wave->SetCurrent(Vec3d(-1.0, -0.0, 0));
	wave->SetVerticalDirection(Dir3d(.1, 0, 0.99498743710662));
	wave->SetPointOnWater(Pnt3d(75, 0, 5));
	wave->Perform();

	auto water = Cad_Tools::Triangulation(wave->SurfaceGeometry(), 20, 20);
	Debug_Null_Pointer(water);

	water->ExportToPlt(myFile);

	auto distb = std::make_shared<Marine_SectionDistribution_Uniform>();
	Debug_Null_Pointer(distb);

	distb->SetLower(box.P0().X());
	distb->SetUpper(box.P1().X());
	distb->SetNbSections(10);
	distb->Perform();

	auto maker = std::make_shared<Marine_ModelMaker_Shape>();
	Debug_Null_Pointer(maker);

	maker->LoadShape(myShape);
	maker->LoadDistributor(distb);
	maker->Perform();

	PAUSE;
	return 0;
}