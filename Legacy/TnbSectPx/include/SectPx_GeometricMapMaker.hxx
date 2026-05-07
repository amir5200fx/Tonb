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
	class SectPx_FrameRegistry;

	namespace maker
	{

		class GeometricMap
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}


			GeometricMap()
			{}

		public:

			GeometricMap
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theReg
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theReg)
			{}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_GeoMap>
				SelectGeoMap
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateLinearInterpolation
				(
					const std::shared_ptr<SectPx_Coord>& theQ0,
					const std::shared_ptr<SectPx_Coord>& theQ1,
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateLinearInterpolation() const;

			TnbSectPx_EXPORT Standard_Integer
				CreateIntersection
				(
					const std::shared_ptr<SectPx_Coord>& theQ0,
					const Dir2d& theDir0,
					const std::shared_ptr<SectPx_Par>& theAng0,
					const std::shared_ptr<SectPx_Coord>& theQ1,
					const Dir2d& theDir1,
					const std::shared_ptr<SectPx_Par>& theAng1
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateIntersection() const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_GeoMap>
				RemoveGeoMap
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::GeometricMap);

#endif // !_SectPx_GeometricMapMaker_Header
