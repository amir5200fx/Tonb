#pragma once
#ifndef _Geo_API_Header
#define _Geo_API_Header
#include <Entity3d_BoxFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_ChaiscriptFwd.hxx>

// Forward Declarations
class gp_Ax2d;
class gp_Ax2;

#include <memory>

namespace tnbLib
{
	// Forward Declarations
	class Pnt3d;
	class Pnt2d;
	class Dir2d;
	class Dir3d;
	class Vec2d;
	class Vec3d;

	namespace api
	{
		namespace geo
		{
			namespace twodim
			{
				struct Box { std::shared_ptr<Entity2d_Box> obj; };
			}

			namespace threedim
			{
				struct Box { std::shared_ptr<Entity3d_Box> obj; };
			}
			TnbGeo_EXPORT Pnt2d make_pnt_2d(double x, double y);
			TnbGeo_EXPORT Pnt3d make_pnt_3d(double x, double y, double z);

			TnbGeo_EXPORT Dir2d make_dir_2d(double u, double v);
			TnbGeo_EXPORT Dir3d make_dir_3d(double u, double v, double w);

			TnbGeo_EXPORT Vec2d make_vec_2d(double u, double v);
			TnbGeo_EXPORT Vec3d make_vec_3d(double u, double v, double w);

			TnbGeo_EXPORT gp_Ax2 make_ax_2(const Pnt3d& c, const Dir3d& n, const Dir3d& vx);
			TnbGeo_EXPORT gp_Ax2 make_ax_2(const Pnt3d& c, const Dir3d& v);

			TnbGeo_EXPORT gp_Ax2d make_ax_2d(const Pnt2d& c, const Dir2d& v);

			TnbGeo_EXPORT threedim::Box make_box_3d(const Pnt3d& p0, const Pnt3d& p1);
			TnbGeo_EXPORT twodim::Box make_box_2d(const Pnt2d& p0, const Pnt2d& p1);

		}
	}

	namespace chai
	{
		struct Geo2d {};
		struct Geo3d {};

		namespace geo
		{
			TnbGeo_EXPORT void functions(const module_t&);
		}
	}
}
#endif