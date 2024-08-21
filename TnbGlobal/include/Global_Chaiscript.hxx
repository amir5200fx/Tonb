#pragma once
#ifndef _Global_Chaiscript_Header
#define _Global_Chaiscript_Header
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
		extern chaiscript::ChaiScript obj;
	}
}
#endif