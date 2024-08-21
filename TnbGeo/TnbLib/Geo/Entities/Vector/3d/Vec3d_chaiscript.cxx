#include <Vec3d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_vec_3d(const module_t& mod)
{
	mod->add(chaiscript::fun([](double u, double v, double w)-> auto {return Vec3d(u, v, w); }), "make_vec_3d");
}