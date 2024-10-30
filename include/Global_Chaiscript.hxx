#pragma once
#ifndef _Global_Chaiscript_Header
#define _Global_Chaiscript_Header
#include <Global_Module.hxx>
#include <memory>
namespace chaiscript
{
	class Module;
	class ChaiScript;
}

namespace tnbLib
{
	using module_t = std::shared_ptr<chaiscript::Module>;
	namespace chai
	{
		struct App{};

		//extern TnbGlobal_EXPORT chaiscript::ChaiScript obj;

		namespace app
		{
			TnbGlobal_EXPORT void functions(const module_t&);
		}
	}
}
#endif