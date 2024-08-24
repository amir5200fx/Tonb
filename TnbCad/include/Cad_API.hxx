#pragma once
#ifndef _TnbCad_API_Header
#define _TnbCad_API_Header
#include <Cad_Module.hxx>
#include <Global_ChaiscriptFwd.hxx>
#include <memory>
#include <string>

// Forward Declarations
class gp_Ax2;

namespace tnbLib
{
	// Forward Declarations
	class Cad_Shape;
	class Pnt3d;

	namespace api
	{
		namespace cad
		{

			struct Shape
			{
				std::shared_ptr<Cad_Shape> shape;
			};

			TnbCad_EXPORT Shape make_box(const Pnt3d& p0, const Pnt3d& p1);
			TnbCad_EXPORT Shape make_box(const Pnt3d& p0, const Pnt3d& p1, const std::string& name);
			TnbCad_EXPORT Shape make_box(const Pnt3d& p0, double dx, double dy, double dz);
			TnbCad_EXPORT Shape make_box(const Pnt3d& p0, double dx, double dy, double dz, const std::string& name);
			TnbCad_EXPORT Shape make_box(const gp_Ax2&, double dx, double dy, double dz);
			TnbCad_EXPORT Shape make_box(const gp_Ax2&, double dx, double dy, double dz, const std::string& name);

			TnbCad_EXPORT Shape make_cylinder(const gp_Ax2&, double r, double h);
			TnbCad_EXPORT Shape make_cylinder(const gp_Ax2&, double r, double h, const std::string&);
			TnbCad_EXPORT Shape make_cylinder(const gp_Ax2&, double r, double h, double angle);
			TnbCad_EXPORT Shape make_cylinder(const gp_Ax2&, double r, double h, double angle, const std::string&);

			TnbCad_EXPORT Shape make_sphere(const Pnt3d& c, double r);
			TnbCad_EXPORT Shape make_sphere(const Pnt3d& c, double r, const std::string& name);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, const std::string& name);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, double angle1);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, double angle1, const std::string& name);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, double angle1, double angle2);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, double angle1, double angle2, const std::string& name);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, double angle1, double angle2, double angle3);
			TnbCad_EXPORT Shape make_sphere(const gp_Ax2& ax, double r, double angle1, double angle2, double angle3, const std::string& name);

			// for loading the file no extension should be used. The file extension is automatically added to the file name.
			TnbCad_EXPORT Shape load_shape(const std::string& file_name, unsigned short verbose);

			TnbCad_EXPORT void export_to_step(const Shape&, const std::string& name);
			TnbCad_EXPORT void export_to_iges(const Shape&, const std::string& name, const std::string& unit);
			TnbCad_EXPORT void save_to(const Shape&, const std::string& name, unsigned short verbose);
		}
	}

	namespace chai
	{
		struct Cad{};
		namespace cad
		{
			TnbCad_EXPORT void functions(const module_t&);
		}
	}
}
#endif