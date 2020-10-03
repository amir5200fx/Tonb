#pragma once
#ifndef _SectPx_PointMaker_Header
#define _SectPx_PointMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_Pnt;
	class SectPx_GeoMap;
	class SectPx_MasterPnt;

	namespace maker
	{

		class Point
			: public SectPx_Maker
		{

			/*Private Data*/

		public:

			explicit Point
			(
				const std::shared_ptr<SectPx_Registry>& theRegistry
			)
				: SectPx_Maker(theRegistry)
			{}

			std::shared_ptr<SectPx_Pnt>
				SelectPnt
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer
				CreateOuterComponent
				(
					const std::shared_ptr<SectPx_Par>& xPar,
					const std::shared_ptr<SectPx_Par>& yPar
				);

			Standard_Integer
				CreateInnerComponent
				(
					const std::shared_ptr<SectPx_Par>& xPar,
					const std::shared_ptr<SectPx_Par>& yPar
				);

			Standard_Integer
				CreateField
				(
					const std::shared_ptr<SectPx_GeoMap>& theMap
				);

			Standard_Integer
				CreateEmpty
				(
					const std::shared_ptr<SectPx_MasterPnt>& theMaster
				);

			std::shared_ptr<SectPx_Pnt> 
				RemovePnt
				(
					const Standard_Integer theIndex
				);
		};
	}
}

#endif // !_SectPx_PointMaker_Header
