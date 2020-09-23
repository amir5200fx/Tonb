#include <Tnb_Examples.hxx>

#include <Pnt2d.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Boolean.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::example_union_plane_box()
{
	auto p0 = Pnt2d(0.1, -0.3);
	auto p1 = Pnt2d(1.03, 0.84);

	auto shape0 = Cad2d_Plane::MakeBox(p0, p1);
	Debug_Null_Pointer(shape0);

	auto shape1 = Cad2d_Plane::MakeBox(p0 + 0.5, p1 + 0.5);
	Debug_Null_Pointer(shape1);

	auto opt = Cad2d_Boolean::Union(shape0, shape1);
	Debug_Null_Pointer(opt);

	/*auto info = std::make_shared<Geo_ApprxCurve_Info>();
	shape->Approx(info);*/

	fileName myFileName("example_union_plane_box.plt");
	OFstream myFile(myFileName);

	opt->ExportToPlt(myFile);
}