#include <Standard_TypeDef.hxx>

#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <TnbCad2d_System.hxx>
#include <dimensionedScalar.hxx>

#include <Marine_FlatWave.hxx>
#include <LegModel_DispNo1.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_System.hxx>

#include <Poly_Triangulation.hxx>

#include <armadillo.h>

using namespace tnbLib;

Standard_Integer main()
{

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

	Cad_FastDiscrete::Triangulation(myShape, *sysLib::gl_fast_discrete_parameters);

	auto myTris = Cad_Tools::RetrieveTriangulation(myShape);

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}

	Entity3d_Box domain(Pnt3d(0, 0, 0), Pnt3d(1, 1, 0.5));
	auto wave = std::make_shared<Marine_FlatWave>(domain);
	Debug_Null_Pointer(wave);

	wave->SetCurrent(Vec3d(-1.0, 0, 0));
	wave->SetVerticalDirection(Dir3d(0, 0, 1));
	wave->Perform();


	

	PAUSE;
	return 0;
}