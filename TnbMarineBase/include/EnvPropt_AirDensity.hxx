#pragma once
#ifndef _EnvPropt_AirDensity_Header
#define _EnvPropt_AirDensity_Header

#include <EnvPropt_Density.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class AirDensity
			: public Density
		{

			/*Private Data*/

		public:

			TnbMarine_EXPORT AirDensity();

			TnbMarine_EXPORT explicit AirDensity(const Standard_Real theValue);
		};
	}
}

#endif // !_EnvPropt_AirDensity_Header
