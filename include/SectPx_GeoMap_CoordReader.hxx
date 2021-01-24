#pragma once
#ifndef _SectPx_GeoMap_CoordReader_Header
#define _SectPx_GeoMap_CoordReader_Header

#include <SectPx_GeoMap.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;
	class SectPx_Par;
	class SectPx_FrameRegistry;


	namespace sectPxLib
	{

		class GeoMap_CoordReader
			: public SectPx_GeoMap
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Coord> theCoord_;


			//- public functions and operators

			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			GeoMap_CoordReader()
			{}

			TnbSectPx_EXPORT GeoMap_CoordReader
			(
				const Standard_Integer theIndex, 
				const word& theName
			);

			const auto& Coord() const
			{
				return theCoord_;
			}

			TnbSectPx_EXPORT void SetCoord
			(
				const std::shared_ptr<SectPx_Coord>& theQ
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			//- override virtual functions from geoMap abstract class 

			TnbSectPx_EXPORT Pnt2d CalcCoord() const override;

			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
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

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> 
				RetrieveChildren() const override;


			static TnbSectPx_EXPORT std::shared_ptr<GeoMap_CoordReader>
				MakeReader
				(
					const std::shared_ptr<SectPx_FrameRegistry>& theReg
				);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::GeoMap_CoordReader);

#endif // !_SectPx_GeoMap_CoordReader_Header
