#pragma once
#ifndef _SectPx_Pnt_GeoField_Header
#define _SectPx_Pnt_GeoField_Header

#include <SectPx_MasterPnt.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_GeoMap;

	namespace sectPxLib
	{

		class Pnt_GeoField
			: public SectPx_MasterPnt
		{

			/*Private Data*/

			std::shared_ptr<SectPx_GeoMap> theMap_;


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		protected:

			template<class... _Types>
			Pnt_GeoField(_Types&&... _Args)
				: SectPx_MasterPnt(_Args...)
			{}

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			const auto& GeoMap() const
			{
				return theMap_;
			}

			TnbSectPx_EXPORT void SetGeoMap
			(
				const std::shared_ptr<SectPx_GeoMap>& theMap
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class
			TnbSectPx_EXPORT Standard_Real xCoord() const override;

			TnbSectPx_EXPORT Standard_Real yCoord() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

			//- override virtual functions from pnt abstract class 
			TnbSectPx_EXPORT sectPxLib::pntType PntType() const override;

			//- override virtual functions from master abstract class 
			TnbSectPx_EXPORT Standard_Boolean IsGeoField() const override;

			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildMaps() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildMap() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Parent> ChildMap(const Standard_Integer theIndex) const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::sectPxLib::Pnt_GeoField);

#include <SectPx_PntConstructor.hxx>

namespace tnbLib
{
	namespace sectPxLib
	{

		template<>
		class OuterPnt<Pnt_GeoField>
			: public Pnt_GeoField
		{};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_GeoField>);

#endif // !_SectPx_Pnt_GeoField_Header
