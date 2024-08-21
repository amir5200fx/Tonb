#include <Dir2d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_dir_2d(const module_t& mod)
{
	mod->add(chaiscript::fun([](double u, double v)-> auto {return Dir2d(u, v); }), "make_dir_2d");
}