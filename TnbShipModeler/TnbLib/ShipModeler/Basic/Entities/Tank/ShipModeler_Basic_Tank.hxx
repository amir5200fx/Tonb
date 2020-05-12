#pragma once
#ifndef _ShipModeler_Basic_Tank_Header
#define _ShipModeler_Basic_Tank_Header

#include <ShipModeler_Basic_Volume.hxx>

namespace tnbLib
{

	namespace shipModelerLib
	{

		class Basic_Tank
			: public Basic_Volume
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Basic_Tank(_Types&&... _Args)
				: Basic_Volume(_Args...)
			{}

			Standard_Boolean IsHull() const override
			{
				return Standard_True;
			}

		};
	}
}

#endif // !_ShipModeler_Basic_Tank_Header
