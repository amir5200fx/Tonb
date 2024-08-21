#include <Vec2d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_vec_2d(const module_t& mod)
{
	mod->add(chaiscript::fun([](double u, double v)-> auto {return Vec2d(u, v); }), "make_vec_2d");
}