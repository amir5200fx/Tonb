#include <Entity3d_Axis.hxx>

#include <Pnt3d.hxx>
#include <Dir3d.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_ax_2(const module_t& mod)
{
	mod->add(chaiscript::fun([](const Pnt3d& c, const Dir3d& n, const Dir3d& vx)-> auto {return make_ax2(c, n, vx); }), "make_ax2");
	mod->add(chaiscript::fun([](const Pnt3d& c, const Dir3d& v)-> auto {return make_ax2(c, v); }), "make_ax2");
}