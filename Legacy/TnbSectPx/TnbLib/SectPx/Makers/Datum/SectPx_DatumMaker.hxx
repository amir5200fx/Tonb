#pragma once
#ifndef _SectPx_DatumMaker_Header
#define _SectPx_DatumMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_Datum;
	class SectPx_GeoMap;
	class Pnt2d;
	class SectPx_FrameRegistry;


	namespace maker
	{

		class Datum
			: public SectPx_Maker<SectPx_FrameRegistry>
		{


			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}


			Datum()
			{}

		public:

			explicit Datum
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theRegistry)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_Datum>
				SelectPnt
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateComponent
				(
					const std::shared_ptr<SectPx_Par>& xPar,
					const std::shared_ptr<SectPx_Par>& yPar
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateField
				(
					const std::shared_ptr<SectPx_GeoMap>& theMap
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Datum>
				RemovePnt
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Datum);

#endif // !_SectPx_DatumMaker_Header
