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
			mod->add(chaiscript::fun([](const Geo2d&, double x, double y)-> auto {return api::geo::make_pnt_2d(x, y); }), "make_pnt");
			mod->add(chaiscript::fun([](const Pnt2d& p)-> auto {return p.X(); }), "x");
			mod->add(chaiscript::fun([](const Pnt3d& p)-> auto {return p.Y(); }), "y");
		}
		void add_pnt_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo3d&, double x, double y, double z)->auto {return api::geo::make_pnt_3d(x, y, z); }), "make_pnt");
			mod->add(chaiscript::fun([](const Pnt3d& p)-> auto {return p.X(); }), "x");
			mod->add(chaiscript::fun([](const Pnt3d& p)-> auto {return p.Y(); }), "y");
			mod->add(chaiscript::fun([](const Pnt3d& p)-> auto {return p.Z(); }), "z");
		}

		void add_vec_2d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo2d&, double u, double v)->auto {return api::geo::make_vec_2d(u, v); }), "make_vec");
			mod->add(chaiscript::fun([](const Vec2d& v)-> auto {return v.X(); }), "u");
			mod->add(chaiscript::fun([](const Vec2d& v)-> auto {return v.Y(); }), "v");
		}
		void add_vec_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo3d&, double u, double v, double w)-> auto {return api::geo::make_vec_3d(u, v, w); }), "make_vec");
			mod->add(chaiscript::fun([](const Vec3d& v)-> auto {return v.X(); }), "u");
			mod->add(chaiscript::fun([](const Vec3d& v)-> auto {return v.Y(); }), "v");
			mod->add(chaiscript::fun([](const Vec3d& v)-> auto {return v.Z(); }), "w");
		}

		void add_dir_2d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo2d&, double u, double v)-> auto {return api::geo::make_dir_2d(u, v); }), "make_dir");
			mod->add(chaiscript::fun([](const Dir2d& v)-> auto {return v.X(); }), "u");
			mod->add(chaiscript::fun([](const Dir2d& v)-> auto {return v.Y(); }), "v");
		}
		void add_dir_3d(const module_t& mod)
		{
			mod->add(chaiscript::fun([](const Geo3d&, double u, double v, double w)-> auto {return api::geo::make_dir_3d(u, v, w); }), "make_dir");
			mod->add(chaiscript::fun([](const Dir3d& d)->auto {return d.X(); }), "u");
			mod->add(chaiscript::fun([](const Dir3d& d)-> auto {return d.Y(); }), "v");
			mod->add(chaiscript::fun([](const Dir3d& d)-> auto {return d.Z(); }), "w");
		}

		void add_box_2d(const module_t& mod)
		{
			using Box = api::geo::twodim::Box;
			mod->add(chaiscript::fun([](const Geo2d&, const Pnt2d& p0, const Pnt2d& p1)-> auto {return api::geo::make_box_2d(p0, p1); }), "make_box");
			mod->add(chaiscript::fun([](const Box& b)->auto {return b.obj->P0(); }), "p0");
			mod->add(chaiscript::fun([](const Box& b)->auto {return b.obj->P1(); }), "p1");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return b.obj->Diameter(); }), "dia");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return std::get<0>(b.obj->Length()); }), "dx");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return std::get<1>(b.obj->Length()); }), "dy");
		}
		void add_box_3d(const module_t& mod)
		{
			using Box = api::geo::threedim::Box;
			mod->add(chaiscript::fun([](const Geo3d&, const Pnt3d& p0, const Pnt3d& p1)-> auto {return api::geo::make_box_3d(p0, p1); }), "make_box");
			mod->add(chaiscript::fun([](const Box& b)->auto {return b.obj->P0(); }), "p0");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return b.obj->P1(); }), "p1");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return b.obj->Diameter(); }), "dia");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return std::get<0>(b.obj->Length()); }), "dx");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return std::get<1>(b.obj->Length()); }), "dy");
			mod->add(chaiscript::fun([](const Box& b)-> auto {return std::get<2>(b.obj->Length()); }), "dz");
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
	mod->add(chaiscript::user_type<Geo2d>(), "Geo2D");
	mod->add(chaiscript::constructor<Geo2d()>(), "Geo2D");
	mod->add(chaiscript::user_type<Geo3d>(), "Geo3D");
	mod->add(chaiscript::constructor<Geo3d()>(), "Geo3D");

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