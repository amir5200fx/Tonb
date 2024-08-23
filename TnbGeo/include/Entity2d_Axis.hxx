#pragma once
#ifndef _Entity2d_Axis_Header
#define _Entity2d_Axis_Header
#include <Geo_Module.hxx>
#include <Global_ChaiscriptFwd.hxx>

#include <gp_Ax2d.hxx>

namespace tnbLib
{
	// Forward Declarations
	class Pnt2d;
	class Dir2d;

	TnbGeo_EXPORT gp_Ax2d make_ax2d(const Pnt2d& theCoord, const Dir2d&);

	namespace chai
	{
		TnbGeo_EXPORT void add_ax_2d(const module_t&);
	}
}
#endif