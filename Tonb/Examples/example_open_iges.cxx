#include <Tnb_Examples.hxx>

#include <Entity3d_Triangulation.hxx>
#include <CadIO_IGES.hxx>
#include <CadIO_STEP.hxx>
#include <Cad_Tools.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_System.hxx>
#include <FastDiscrete_Params.hxx>
#include <OFstream.hxx>

#include <Bnd_Box.hxx>
#include <Poly_Triangulation.hxx>
#include <TopoDS_Shape.hxx>

using namespace tnbLib;

void tnbLib::example_open_iges()
{
	CadIO_IGES reader;
	reader.ReadFile("KCS_hull_SVA.igs");

	auto myShape = reader.Shape();

	auto b0 = Cad_Tools::BoundingBox(myShape);
	auto box = Cad_Tools::BoundingBox(b0);

	fileName name("example_open_iges.plt");
	OFstream myFile(name);

	FastDiscrete_Params params;
	params.Deflection = 1.0e-4*box.Diameter();
	params.Angle = 2.0;

	Cad_FastDiscrete::Triangulation(myShape, params);

	auto myTris = Cad_Tools::RetrieveTriangulation(myShape);

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}
}