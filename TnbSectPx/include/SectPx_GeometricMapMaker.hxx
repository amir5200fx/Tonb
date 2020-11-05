#pragma once
#ifndef _SectPx_GeometricMapMaker_Header
#define _SectPx_GeometricMapMaker_Header

#include <SectPx_Maker.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_GeoMap;
	class SectPx_Coord;
	class SectPx_Par;

	namespace maker
	{

		class GeometricMap
			: public SectPx_Maker
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker>(*this);
			}


			GeometricMap()
			{}

		public:

			GeometricMap
			(
				const std::shared_ptr<SectPx_Registry>& theReg
			)
				: SectPx_Maker(theReg)
			{}

			std::shared_ptr<SectPx_GeoMap>
				SelectGeoMap
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer
				CreateLinearInterpolation
				(
					const std::shared_ptr<SectPx_Coord>& theQ0,
					const std::shared_ptr<SectPx_Coord>& theQ1,
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			Standard_Integer
				CreateLinearInterpolation() const;

			Standard_Integer
				CreateIntersection
				(
					const std::shared_ptr<SectPx_Coord>& theQ0,
					const Dir2d& theDir0,
					const std::shared_ptr<SectPx_Par>& theAng0,
					const std::shared_ptr<SectPx_Coord>& theQ1,
					const Dir2d& theDir1,
					const std::shared_ptr<SectPx_Par>& theAng1
				) const;

			Standard_Integer
				CreateIntersection() const;

			std::shared_ptr<SectPx_GeoMap>
				RemoveGeoMap
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

#endif // !_SectPx_GeometricMapMaker_Header
