#pragma once
#ifndef _Marine_System_Header
#define _Marine_System_Header

#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;

	namespace sysLib
	{

		TnbMarine_EXPORT extern std::shared_ptr<NumAlg_AdaptiveInteg_Info> gl_marine_integration_info;

		TnbMarine_EXPORT void init_gl_marine_integration_info();
	}
}

#endif // !_Marine_System_Header
