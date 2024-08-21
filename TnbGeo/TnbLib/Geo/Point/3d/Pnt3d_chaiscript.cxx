#include <Pnt3d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_pnt_3d(const module_t& mod)
{
	mod->add(chaiscript::fun([](double x, double y, double z)-> auto {return Pnt3d(x, y, z); }), "make_pnt_3d");
}