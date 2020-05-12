#pragma once
#ifndef _ShipModeler_Basic_Hull_Header
#define _ShipModeler_Basic_Hull_Header

#include <ShipModeler_Basic_Volume.hxx>

namespace tnbLib
{

	namespace shipModelerLib
	{

		class Basic_Hull
			: public Basic_Volume
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Basic_Hull(_Types&&... _Args)
				: Basic_Volume(_Args...)
			{}

			Standard_Boolean IsHull() const override
			{
				return Standard_True;
			}

		};
	}
}

#endif // !_ShipModeler_Basic_Hull_Header
