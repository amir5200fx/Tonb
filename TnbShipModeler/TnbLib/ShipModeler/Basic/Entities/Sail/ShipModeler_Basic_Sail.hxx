#pragma once
#ifndef _ShipModeler_Basic_Sail_Header
#define _ShipModeler_Basic_Sail_Header

#include <ShipModeler_Basic_Volume.hxx>

namespace tnbLib
{

	namespace shipModelerLib
	{

		class Basic_Sail
			: public Basic_Volume
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Basic_Sail(_Types&&... _Args)
				: Basic_Volume(_Args...)
			{}

			Standard_Boolean IsSail() const override
			{
				return Standard_True;
			}

		};
	}
}

#endif // !_ShipModeler_Basic_Sail_Header
