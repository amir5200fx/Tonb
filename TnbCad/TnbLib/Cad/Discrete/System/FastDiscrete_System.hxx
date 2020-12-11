#pragma once
#ifndef _FastDiscrete_System_Header
#define _FastDiscrete_System_Header

#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	struct FastDiscrete_Params;

	namespace sysLib
	{

		extern TnbCad_EXPORT std::shared_ptr<FastDiscrete_Params> gl_fast_discrete_parameters;
	}
}

#endif // !_FastDiscrete_System_Header
