#pragma once
#ifndef _HydStatic_StaticEquilib_Header
#define _HydStatic_StaticEquilib_Header

#include <HydStatic_Equilib.hxx>

namespace tnbLib
{

	class HydStatic_StaticEquilib
		: public HydStatic_Equilib
	{

		/*Private Data*/

	public:


		void Perform();
	};
}

#endif // !_HydStatic_StaticEquilib_Header
