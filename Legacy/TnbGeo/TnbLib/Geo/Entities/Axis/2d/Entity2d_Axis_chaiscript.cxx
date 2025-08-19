#include <Entity2d_Axis.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_ax_2d(const module_t& mod)
{
	mod->add(chaiscript::fun([](const Pnt2d& pt, const Dir2d& d)-> auto {return make_ax2d(pt, d); }), "make_ax_2d");
}