#pragma once
#ifndef _Entity3d_Axis_Header
#define _Entity3d_Axis_Header
#include <Geo_Module.hxx>
#include <Global_ChaiscriptFwd.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{
	// Forward Declarations
	class Pnt3d;
	class Dir3d;

	TnbGeo_EXPORT gp_Ax2 make_ax2(const Pnt3d& c, const Dir3d& n, const Dir3d& vx);
	TnbGeo_EXPORT gp_Ax2 make_ax2(const Pnt3d& c, const Dir3d& v);

	namespace chai
	{
		TnbGeo_EXPORT void add_ax_2(const module_t&);
	}
}
#endif