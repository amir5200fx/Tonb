#pragma once
#ifndef _Cad2d_Plane_System_Header
#define _Cad2d_Plane_System_Header

#include <memory>
#include <Cad2d_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane_Info;

	namespace sysLib
	{

		TnbCad2d_EXPORT extern std::shared_ptr<Cad2d_Plane_Info> gl_cad2d_plane_info;

		TnbCad2d_EXPORT void init_gl_cad2d_plane_info();
	}
}

#endif // !_Cad2d_Plane_System_Header
