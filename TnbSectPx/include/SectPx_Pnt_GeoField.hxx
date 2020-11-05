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

			static const char* typeName_;

			const auto& GeoMap() const
			{
				return theMap_;
			}

			void SetGeoMap
			(
				const std::shared_ptr<SectPx_GeoMap>& theMap
			);

			word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class
			Standard_Real xCoord() const override;

			Standard_Real yCoord() const override;

			Pnt2d Coord() const override;

			Standard_Boolean IsComplete() const override;

			//- override virtual functions from pnt abstract class 
			sectPxLib::pntType PntType() const override;

			//- override virtual functions from master abstract class 
			Standard_Boolean IsGeoField() const override;

			//- override virtual functions from parent abstract class 

			Standard_Integer NbChildMaps() const override;

			Standard_Boolean HasChildMap() const override;

			Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			std::shared_ptr<SectPx_Parent> ChildMap(const Standard_Integer theIndex) const override;

			void RemoveThisFromChildren() const override;

			void AddThisToChildren() const override;

			void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		};
	}
}

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

#endif // !_SectPx_Pnt_GeoField_Header
