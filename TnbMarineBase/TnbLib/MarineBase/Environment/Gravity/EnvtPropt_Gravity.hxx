#pragma once
#ifndef _EnvtPropt_Gravity_Header
#define _EnvtPropt_Gravity_Header

#include <Marine_EnvtParamM.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		MARINE_ENVTPARAM(Gravity, "gravity", dimLength / (dimTime * dimTime))
	}
}

#endif // !_EnvtPropt_Gravity_Header
