#include <Tnb_Examples.hxx>

#include <Geo_ApprxCurve_Info.hxx>
#include <Pnt2d.hxx>
#include <Cad2d_Plane.hxx>

void tnbLib::example_creating_plane_box()
{
	auto p0 = Pnt2d(0.1, -0.3);
	auto p1 = Pnt2d(1.03, 0.84);

	auto shape = Cad2d_Plane::MakeBox(p0, p1);
	Debug_Null_Pointer(shape);

	auto info = std::make_shared<Geo_ApprxCurve_Info>();
	shape->Approx(info);

	fileName myFileName("example_creating_plane_box.plt");
	OFstream myFile(myFileName);

	shape->ExportToPlt(myFile);
}