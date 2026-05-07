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
	class SectPx_FrameRegistry;

	namespace maker
	{

		class Point
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}


			Point()
			{}

		public:

			explicit Point
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theRegistry)
			{}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pnt>
				SelectPnt
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateOuterComponent
				(
					const std::shared_ptr<SectPx_Par>& xPar,
					const std::shared_ptr<SectPx_Par>& yPar
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateInnerComponent
				(
					const std::shared_ptr<SectPx_Par>& xPar,
					const std::shared_ptr<SectPx_Par>& yPar
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateOuterOffset
				(
					const Standard_Real x, 
					const Standard_Real y
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateOuterOffset
				(
					const Pnt2d& pt
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateInnerOffset
				(
					const Standard_Real x, 
					const Standard_Real y
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateInnerOffset
				(
					const Pnt2d& pt
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateField
				(
					const std::shared_ptr<SectPx_GeoMap>& theMap
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateEmpty
				(
					const std::shared_ptr<SectPx_MasterPnt>& theMaster
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pnt>
				RemovePnt
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Point);

#endif // !_SectPx_PointMaker_Header
