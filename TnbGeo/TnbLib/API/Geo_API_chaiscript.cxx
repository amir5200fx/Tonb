#include <Geo_API.hxx>

#include <Entity3d_Box.hxx>
#include <Entity2d_Box.hxx>
#include <Pnt3d.hxx>
#include <Vec3d.hxx>
#include <Dir3d.hxx>
#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Dir2d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

//namespace tnbLib
//{
//	namespace api
//	{
//		namespace geo
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
//static const tnbLib::api::geo::RegisterChaiFunctions RegisterChaiFunctionsObj;

#include <Global_Chaiscript.hxx>

namespace tnbLib
{
	namespace chai
	{
		void add_pnt_2d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, double x, double y)-> auto {return api::geo::make_pnt_2d(x, y); }), "make_pnt");
		}
		void add_pnt_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, double x, double y, double z)->auto {return api::geo::make_pnt_3d(x, y, z); }), "make_pnt");
		}

		void add_vec_2d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, double u, double v)->auto {return api::geo::make_vec_2d(u, v); }), "make_vec");
		}
		void add_vec_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, double u, double v, double w)-> auto {return api::geo::make_vec_3d(u, v, w); }), "make_vec");
		}

		void add_dir_2d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, double u, double v)-> auto {return api::geo::make_dir_2d(u, v); }), "make_dir");
		}
		void add_dir_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, double u, double v, double w)-> auto {return api::geo::make_dir_3d(u, v, w); }), "make_dir");
		}

		void add_box_2d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, const Pnt2d& p0, const Pnt2d& p1)-> auto {return api::geo::make_box_2d(p0, p1); }), "make_box");
		}
		void add_box_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo&, const Pnt3d& p0, const Pnt3d& p1)-> auto {return api::geo::make_box_3d(p0, p1); }), "make_box");
		}
	}
}

//void tnbLib::api::geo::RegisterChaiFunctions::add_functions()
//{
//	auto mod = std::make_shared<chaiscript::Module>();
//
//	chai::add_pnt_3d(mod);
//	chai::add_pnt_2d(mod);
//
//	chai::add_vec_2d(mod);
//	chai::add_vec_3d(mod);
//
//	chai::add_dir_2d(mod);
//	chai::add_dir_3d(mod);
//
//	chai::add_box_2d(mod);
//	chai::add_box_3d(mod);
//
//	chai::obj.add(mod);
//}

void tnbLib::chai::geo::functions(const module_t& mod)
{
	mod->add(chaiscript::user_type<Geo>(), "Geometry");
	mod->add(chaiscript::constructor<Geo()>(), "Geometry");

	add_pnt_3d(mod);
	add_pnt_2d(mod);

	add_vec_2d(mod);
	add_vec_3d(mod);

	add_dir_2d(mod);
	add_dir_3d(mod);

	add_box_2d(mod);
	add_box_3d(mod);

	obj.add(mod);
}