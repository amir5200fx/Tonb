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
	class Pnt2d;

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
				) const;

			Standard_Integer
				CreateInnerComponent
				(
					const std::shared_ptr<SectPx_Par>& xPar,
					const std::shared_ptr<SectPx_Par>& yPar
				) const;

			Standard_Integer 
				CreateOuterOffset
				(
					const Standard_Real x, 
					const Standard_Real y
				) const;

			Standard_Integer 
				CreateOuterOffset
				(
					const Pnt2d& pt
				) const;

			Standard_Integer
				CreateInnerOffset
				(
					const Standard_Real x, 
					const Standard_Real y
				) const;

			Standard_Integer
				CreateInnerOffset
				(
					const Pnt2d& pt
				) const;

			Standard_Integer
				CreateField
				(
					const std::shared_ptr<SectPx_GeoMap>& theMap
				) const;

			Standard_Integer
				CreateEmpty
				(
					const std::shared_ptr<SectPx_MasterPnt>& theMaster
				) const;

			std::shared_ptr<SectPx_Pnt> 
				RemovePnt
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

#endif // !_SectPx_PointMaker_Header
