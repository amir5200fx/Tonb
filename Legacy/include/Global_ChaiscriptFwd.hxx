#pragma once
#ifndef _Global_ChaiscriptFwd_Header
#define _Global_ChaiscriptFwd_Header
namespace chaiscript
{
	class Module;
}
#include <memory>
namespace tnbLib
{
	using module_t = std::shared_ptr<chaiscript::Module>;
}
#endif