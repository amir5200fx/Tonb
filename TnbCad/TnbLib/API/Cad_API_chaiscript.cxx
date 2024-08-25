#include <Cad_API.hxx>

#include <Cad_Shape.hxx>
#include <Pnt3d.hxx>

#include <gp_Ax2.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

//namespace tnbLib
//{
//	namespace api
//	{
//		namespace cad
//		{
//			class RegisterChaiFunctions
//			{
//				/*Private Data*/
//				static void add_functions();
//			public:
//				// default constructor
//				RegisterChaiFunctions()
//				{
//					add_functions();
//				}
//			};
//		}
//	}
//}
//
//const tnbLib::api::cad::RegisterChaiFunctions RegisterChaiFunctionsObj;

#include <Global_Chaiscript.hxx>

namespace tnbLib
{
	namespace chai
	{
		namespace cad
		{
			void add_box(const module_t& mod)
			{
				mod->add(chaiscript::fun([](const Cad&, const Pnt3d& p0, const Pnt3d& p1)->auto {return api::cad::make_box(p0, p1); }), "make_box");
				mod->add(chaiscript::fun([](const Cad&, const Pnt3d& p0, const Pnt3d& p1, const std::string& name)-> auto {return api::cad::make_box(p0, p1, name); }), "make_box");
				mod->add(chaiscript::fun([](const Cad&, const Pnt3d& p0, double dx, double dy, double dz)-> auto {return api::cad::make_box(p0, dx, dy, dz); }), "make_box");
				mod->add(chaiscript::fun([](const Cad&, const Pnt3d& p0, double dx, double dy, double dz, const std::string& name)-> auto {return api::cad::make_box(p0, dx, dy, dz, name); }), "make_box");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double dx, double dy, double dz)-> auto {return api::cad::make_box(ax, dx, dy, dz); }), "make_box");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double dx, double dy, double dz, const std::string& name)-> auto {return api::cad::make_box(ax, dx, dy, dz, name); }), "make_box");
			}
			void add_cylinder(const module_t& mod)
			{
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double h)-> auto {return api::cad::make_cylinder(ax, r, h); }), "make_cylinder");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double h, const std::string& name)-> auto {return api::cad::make_cylinder(ax, r, h, name); }), "make_cylinder");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double h, double angle)-> auto {return api::cad::make_cylinder(ax, r, h, angle); }), "make_cylinder");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double h, double angle, const std::string& name)->auto {return api::cad::make_cylinder(ax, r, h, angle, name); }), "make_cylinder");
			}
			void add_sphere(const module_t& mod)
			{
				mod->add(chaiscript::fun([](const Cad&, const Pnt3d& c, double r)-> auto {return api::cad::make_sphere(c, r); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const Pnt3d& c, double r, const std::string& name)-> auto {return api::cad::make_sphere(c, r, name); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r)-> auto {return api::cad::make_sphere(ax, r); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, const std::string& name)-> auto {return api::cad::make_sphere(ax, r, name); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r)-> auto {return api::cad::make_sphere(ax, r); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, const std::string& name)-> auto {return api::cad::make_sphere(ax, r, name); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double angle1)-> auto {return api::cad::make_sphere(ax, r, angle1); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double angle1, const std::string& name)-> auto {return api::cad::make_sphere(ax, r, angle1, name); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double angle1, double angle2)-> auto {return api::cad::make_sphere(ax, r, angle1, angle2); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double angle1, double angle2, const std::string& name)-> auto {return api::cad::make_sphere(ax, r, angle1, angle2, name); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double angle1, double angle2, double angle3)-> auto {return api::cad::make_sphere(ax, r, angle1, angle2, angle3); }), "make_sphere");
				mod->add(chaiscript::fun([](const Cad&, const gp_Ax2& ax, double r, double angle1, double angle2, double angle3, const std::string& name)-> auto {return api::cad::make_sphere(ax, r, angle1, angle2, angle3, name); }), "make_sphere");
			}

			void add_io(const module_t& mod)
			{
				mod->add(chaiscript::fun([](const api::cad::Shape& shape, const std::string& name, const std::string& unit)-> void {api::cad::export_to_iges(shape, name, unit); }), "export_to_iges");
				mod->add(chaiscript::fun([](const api::cad::Shape& shape, const std::string& name)-> void {api::cad::export_to_step(shape, name); }), "export_to_step");
				mod->add(chaiscript::fun([](const api::cad::Shape& shape, const std::string& name, unsigned short verbose)-> void {api::cad::save_to(shape, name, verbose); }), "save_to");
				mod->add(chaiscript::fun([](const api::cad::Shape& shape, const std::string& name)-> void {api::cad::save_to(shape, name, 0); }), "save_to");

				// loading a shape file
				mod->add(chaiscript::fun([](const Cad&, const std::string& file_name)->auto {return api::cad::load_shape(file_name, 0); }), "read_shape");
				mod->add(chaiscript::fun([](const Cad&, const std::string& file_name, unsigned short i)-> auto {return api::cad::load_shape(file_name, i); }), "read_shape");

				mod->add(chaiscript::fun([](const Cad&, const std::string& file_name)-> auto {return api::cad::load_iges(file_name, 0); }), "read_iges");
				mod->add(chaiscript::fun([](const Cad&, const std::string& file_name, unsigned short i)-> auto {return api::cad::load_iges(file_name, i); }), "read_iges");
				mod->add(chaiscript::fun([](const Cad&, const std::string& file_name)-> auto {return api::cad::load_step(file_name, 0); }), "read_step");
				mod->add(chaiscript::fun([](const Cad&, const std::string& file_name, unsigned short i)-> auto {return api::cad::load_step(file_name, i); }), "read_step");
			}
		}
	}
}

//void tnbLib::api::cad::RegisterChaiFunctions::add_functions()
//{
//	auto mod = std::make_shared<chaiscript::Module>();
//
//	chai::cad::add_box(mod);
//	chai::cad::add_cylinder(mod);
//	chai::cad::add_sphere(mod);
//	chai::cad::add_io(mod);
//
//	chai::obj.add(mod);
//}

void tnbLib::chai::cad::functions(const module_t& mod)
{
	mod->add(chaiscript::user_type<Cad>(), "Cad");
	mod->add(chaiscript::constructor<Cad()>(), "Cad");

	add_box(mod);
	add_cylinder(mod);
	add_sphere(mod);
	add_io(mod);

	obj.add(mod);
}