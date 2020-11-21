#pragma once
#ifndef _EnvPropt_Velocity_Header
#define _EnvPropt_Velocity_Header

#include <Marine_DimensionedParam.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Velocity
			: public realParam
		{

			/*Private Data*/

		public:

			TnbMarine_EXPORT explicit Velocity(const Standard_Real theValue);
		};
	}
}

#endif // !_EnvPropt_Velocity_Header
