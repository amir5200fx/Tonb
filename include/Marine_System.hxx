#pragma once
#ifndef _Marine_System_Header
#define _Marine_System_Header

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;

	namespace sysLib
	{

		extern std::shared_ptr<NumAlg_AdaptiveInteg_Info> gl_marine_integration_info;

		void init_gl_marine_integration_info();
	}
}

#endif // !_Marine_System_Header
