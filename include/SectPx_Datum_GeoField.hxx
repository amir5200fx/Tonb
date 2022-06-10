#pragma once
#ifndef _SectPx_Datum_GeoField_Header
#define _SectPx_Datum_GeoField_Header

#include <SectPx_Datum.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_GeoMap;

	namespace sectPxLib
	{

		class Datum_GeoField
			: public SectPx_Datum
		{

			/*Private Data*/

			std::shared_ptr<SectPx_GeoMap> theMap_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			Datum_GeoField()
			{}

			TnbSectPx_EXPORT Datum_GeoField
			(
				const Standard_Integer theIndex, 
				const word& theName
			);

			const auto& GeoMap() const
			{
				return theMap_;
			}

			void SetGeoMap
			(
				const std::shared_ptr<SectPx_GeoMap>& theMap
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Standard_Boolean IsGeoField() const override;

			//- override virtual functions from coord abstract class

			TnbSectPx_EXPORT Standard_Real xCoord() const override;

			TnbSectPx_EXPORT Standard_Real yCoord() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;


			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildMaps() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildMap() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Parent>
				ChildMap
				(
					const Standard_Integer theIndex
				) const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::Datum_GeoField);

#endif // !_SectPx_Datum_GeoField_Header
