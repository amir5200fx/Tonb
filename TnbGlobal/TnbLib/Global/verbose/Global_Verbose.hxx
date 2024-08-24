#pragma once
#ifndef _Global_Verbose_Header
#define _Global_Verbose_Header
#include <Global_Module.hxx>
#include <Global_ChaiscriptFwd.hxx>
namespace tnbLib
{
	extern TnbGlobal_EXPORT unsigned short verbose;

	namespace chai
	{
		TnbGlobal_EXPORT void add_verbose(const module_t&);
	}
}
#endif