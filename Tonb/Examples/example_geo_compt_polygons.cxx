#include <Tnb_Examples.hxx>

#include <Entity2d_Polygon.hxx>
#include <Geo_CmptLib.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Pln_Wire.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

void tnbLib::example_geo_compt_polygons()
{
	auto shape = Cad2d_Plane::MakeBox(Pnt2d(-0.5, -0.15), Pnt2d(0.5, 0.15));
	Debug_Null_Pointer(shape);

	auto poly = shape->OuterWire()->Polygon();
	Debug_Null_Pointer(poly);

	cout << "poly ix = " << Geo_CmptLib::Ix(*poly, 0) << std::endl;

	auto info = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	Debug_Null_Pointer(info);

	info->SetNbInitIterations(2);
	info->SetTolerance(1.0e-4);

	cout << "shape ix = " << Cad2d_CmptLib::Ix(*shape->OuterWire(), 0, info) << std::endl;
}