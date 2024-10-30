#include <Geo_API.hxx>

#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Vec3d.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Vec2d.hxx>

#include <gp_Ax2.hxx>
#include <gp_Ax2d.hxx>

tnbLib::Pnt2d tnbLib::api::geo::make_pnt_2d(double x, double y)
{
	return { x,y };
}

tnbLib::Pnt3d tnbLib::api::geo::make_pnt_3d(double x, double y, double z)
{
	return { x, y, z };
}

tnbLib::Dir2d tnbLib::api::geo::make_dir_2d(double u, double v)
{
	return { u, v };
}

tnbLib::Dir3d tnbLib::api::geo::make_dir_3d(double u, double v, double w)
{
	return { u,v,w };
}

tnbLib::Vec2d tnbLib::api::geo::make_vec_2d(double u, double v)
{
	return { u,v };
}

tnbLib::Vec3d tnbLib::api::geo::make_vec_3d(double u, double v, double w)
{
	return { u,v,w };
}

gp_Ax2 tnbLib::api::geo::make_ax_2(const Pnt3d& c, const Dir3d& n, const Dir3d& vx)
{
	return { c, n, vx };
}

gp_Ax2 tnbLib::api::geo::make_ax_2(const Pnt3d& c, const Dir3d& v)
{
	return { c,v };
}

gp_Ax2d tnbLib::api::geo::make_ax_2d(const Pnt2d& c, const Dir2d& v)
{
	return { c,v };
}

#include <Entity3d_Box.hxx>
#include <Entity2d_Box.hxx>

tnbLib::api::geo::threedim::Box tnbLib::api::geo::make_box_3d(const Pnt3d& p0, const Pnt3d& p1)
{
	return { std::make_shared<Entity3d_Box>(p0, p1) };
}

tnbLib::api::geo::twodim::Box tnbLib::api::geo::make_box_2d(const Pnt2d& p0, const Pnt2d& p1)
{
	return { std::make_shared<Entity2d_Box>(p0, p1) };
}
