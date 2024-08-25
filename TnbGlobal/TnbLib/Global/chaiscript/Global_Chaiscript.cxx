#include <Global_Chaiscript.hxx>
#include <messageStream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

chaiscript::ChaiScript tnbLib::chai::obj;



#include <Global_Verbose.hxx>

void tnbLib::chai::app::functions(const module_t& mod)
{
	mod->add(chaiscript::user_type<App>(), "App");
	mod->add(chaiscript::constructor<App()>(), "App");

	add_verbose(mod);
	mod->add(chaiscript::fun([](const App&, const std::string& str)-> void {Info << str.c_str(); }), "message");
	mod->add(chaiscript::fun([](double x)->auto {return std::to_string(x); }), "to_string");
	mod->add(chaiscript::fun([](int n)->auto {return std::to_string(n); }), "to_string");
	mod->add(chaiscript::fun([](unsigned int i)-> auto {return std::to_string(i); }), "to_string");
}