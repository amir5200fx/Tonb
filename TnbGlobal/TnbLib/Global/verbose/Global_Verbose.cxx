#include <Global_Verbose.hxx>

unsigned short tnbLib::verbose(0);

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::chai::add_verbose(const module_t& mod)
{
	mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "set_verbose");
}
