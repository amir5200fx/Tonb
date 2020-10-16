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

		public:

			static const char* typeName_;

			template<class... _Types>
			Datum_GeoField(_Types&&... _Args)
				: SectPx_Datum(_Args...)
			{}

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


			//- override virtual functions from parent abstract class 

			Standard_Integer NbChildMaps() const override;

			Standard_Boolean HasChildMap() const override;

			Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			std::shared_ptr<SectPx_Parent> 
				ChildMap
				(
					const Standard_Integer theIndex
				) const override;

			void RemoveThisFromChildren() const override;

			void AddThisToChildren() const override;

			void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		};
	}
}

#endif // !_SectPx_Datum_GeoField_Header
