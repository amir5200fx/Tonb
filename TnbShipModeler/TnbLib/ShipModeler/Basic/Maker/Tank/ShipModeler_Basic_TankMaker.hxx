#pragma once
#ifndef _ShipModeler_Basic_TankMaker_Header
#define _ShipModeler_Basic_TankMaker_Header

#include <ShipModeler_Basic_Maker.hxx>

namespace tnbLib
{


	// Forward Declarations
	class Geo_xDistb;
	class Marine_VesselTank;

	namespace shipModelerLib
	{

		class Basic_TankMaker
			: public Basic_Maker
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Basic_TankMaker(_Types&&... _Args)
				: Basic_Maker(_Args...)
			{}

			void ImportHull
			(
				const Marine_VesselTank& theTank,
				const Geo_xDistb& theX
			);

			void CreatePlane
			(
				const Marine_VesselTank& theTank,
				const Standard_Real theX
			);
		};
	}
}

#endif // !_ShipModeler_Basic_TankMaker_Header
