#include <Dir3d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_dir_3d(const module_t& mod)
{
	mod->add(chaiscript::fun([](double x, double y, double z)-> auto {return Pnt3d(x, y, z); }), "make_dir_3d");
}