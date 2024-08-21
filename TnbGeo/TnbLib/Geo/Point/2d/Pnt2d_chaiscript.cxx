#include <Pnt2d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_pnt_2d(const module_t& mod)
{
	mod->add(chaiscript::fun([](double x, double y)-> auto {return Pnt2d(x, y); }), "make_pnt_2d");
}
