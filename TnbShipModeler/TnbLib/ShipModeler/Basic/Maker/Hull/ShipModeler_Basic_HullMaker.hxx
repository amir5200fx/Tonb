#pragma once
#ifndef _ShipModeler_Basic_HullMaker_Header
#define _ShipModeler_Basic_HullMaker_Header

#include <Standard_Handle.hxx>
#include <ShipModeler_Basic_Maker.hxx>

class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_VesselHull;

	namespace shipModelerLib
	{

		class Basic_HullMaker
			: public Basic_Maker
		{

			/*Private Data*/

		public:

			template<class... _Types>
			Basic_HullMaker(_Types&&... _Args)
				: Basic_Maker(_Args...)
			{}

			void ImportHull
			(
				const Marine_VesselHull& theHull,
				const Geo_xDistb& theX
			);

			void CreatePlane
			(
				const Marine_VesselHull& theHull,
				const Standard_Real theX
			);

			
		};
	}
}

#endif // !_ShipModeler_Basic_HullMaker_Header
