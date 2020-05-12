#pragma once
#ifndef _ShipModeler_Basic_SailMaker_Header
#define _ShipModeler_Basic_SailMaker_Header

#include <ShipModeler_Basic_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_VesselSail;

	namespace shipModelerLib
	{

		class Basic_SailMaker
			: public Basic_Maker
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Basic_SailMaker(_Types&&... _Args)
				: Basic_Maker(_Args...)
			{}

			void ImportSail(const Marine_VesselSail& theSail, const Geo_xDistb& theX);

			void CreatePlane(const Marine_VesselSail& theSail, const Standard_Real x);
		};
	}
}

#endif // !_ShipModeler_Basic_SailMaker_Header
