#include <Tnb_Examples.hxx>

#include <gp.hxx>
#include <Dir2d.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_CmptLib.hxx>
#include <UnitSystem.hxx>
#include <error.hxx>
#include <OSstream.hxx>

using namespace tnbLib;

void tnbLib::example_transform_shape2d()
{
	fileName myFileName("example_transform_shape2d.plt");
	OFstream myFile(myFileName);

	auto shape = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1.0, 0.3));
	Debug_Null_Pointer(shape);

	auto c_shape = std::dynamic_pointer_cast<Cad2d_Plane>(shape->Copy());

	auto sys0 = gp::OX2d();

	Pnt2d p1(0, 0);
	Dir2d dir(0.8, 0.2);

	gp_Ax2d sys1(p1, dir);

	/*gp_Trsf2d t;
	t.SetRotation(Pnt2d(0, 0), ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*10);*/

	auto t = Cad2d_CmptLib::Transform(sys0, sys1);
	c_shape->Transform(t);

	c_shape->ExportToPlt(myFile);
}