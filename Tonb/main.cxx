#include <Standard_TypeDef.hxx>

#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <TnbCad2d_System.hxx>

#include <armadillo.h>

using namespace tnbLib;

Standard_Integer main()
{

	sysLib::init_TnbCad2d();

	auto pln = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1.0, 0.38), sysLib::gl_cad2d_plane_info);
	Debug_Null_Pointer(pln);



	return 0;
}