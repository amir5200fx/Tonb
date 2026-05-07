#include <Cad2d_Plane_System.hxx>

#include <Cad2d_Plane_Info.hxx>
#include <Geo_ApprxCurve_System.hxx>

namespace tnbLib
{

	TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane_Info> sysLib::gl_cad2d_plane_info =
		std::make_shared<Cad2d_Plane_Info>();
}

void tnbLib::sysLib::init_gl_cad2d_plane_info()
{
	auto& inf = *gl_cad2d_plane_info;
	inf.OverrideApproxInfo(gl_approx_curve2d_info);
}