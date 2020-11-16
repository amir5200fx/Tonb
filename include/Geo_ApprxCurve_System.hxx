#pragma once
#ifndef _Geo_ApprxCurve_System_Header
#define _Geo_ApprxCurve_System_Header

#include <memory>
#include <Geo_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_ApprxCurve_Info;

	namespace sysLib
	{

		extern TnbGeo_EXPORT std::shared_ptr<Geo_ApprxCurve_Info> gl_approx_curve2d_info;
		extern TnbGeo_EXPORT std::shared_ptr<Geo_ApprxCurve_Info> gl_approx_curve3d_info;

		TnbGeo_EXPORT void init_gl_approx_curve_info();
	}
}

#endif // !_Geo_ApprxCurve_System_Header
