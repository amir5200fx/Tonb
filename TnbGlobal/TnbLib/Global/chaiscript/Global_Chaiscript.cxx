#include <Global_Chaiscript.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

chaiscript::ChaiScript tnbLib::chai::obj;

namespace tnbLib
{
	class RegisterChaiFunctions
	{
		/*Private Data*/
		static void add_functions();
	public:
		// default constructors

		// constructors
		RegisterChaiFunctions()
		{
			add_functions();
		}
	};
}

const tnbLib::RegisterChaiFunctions RegisterChaiFunctionsObj;

#include <Global_Verbose.hxx>

void tnbLib::RegisterChaiFunctions::add_functions()
{
	auto mod = std::make_shared<chaiscript::Module>();

	chai::add_verbose(mod);

	chai::obj.add(mod);
}