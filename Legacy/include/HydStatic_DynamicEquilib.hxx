#pragma once
#ifndef _HydStatic_DynamicEquilib_Header
#define _HydStatic_DynamicEquilib_Header

#include <HydStatic_Equilib.hxx>

namespace tnbLib
{

	class HydStatic_DynamicEquilib
		: public HydStatic_Equilib
	{

		/*Private Data*/

	public:


		void Perform();
	};
}

#endif // !_HydStatic_DynamicEquilib_Header
