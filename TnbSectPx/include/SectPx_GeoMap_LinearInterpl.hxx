#pragma once
#ifndef _SectPx_GeoMap_LinearInterpl_Header
#define _SectPx_GeoMap_LinearInterpl_Header

#include <SectPx_GeoMap.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;
	class SectPx_Par;
	class SectPx_Registry;

	namespace sectPxLib
	{

		class GeoMap_LinearInterpl
			: public SectPx_GeoMap
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Coord> theQ0_;
			std::shared_ptr<SectPx_Coord> theQ1_;

			std::weak_ptr<SectPx_Par> thePar_;

		public:

			static const char* typeName_;

			template<class... _Types>
			GeoMap_LinearInterpl(_Types&&... _Args)
				: SectPx_GeoMap(_Args...)
			{}

			const auto& Q0() const
			{
				return theQ0_;
			}

			const auto& Q1() const
			{
				return theQ1_;
			}

			const auto& Par() const
			{
				return thePar_;
			}

			void SetQ0
			(
				const std::shared_ptr<SectPx_Coord>& theQ0
			);

			void SetQ1
			(
				const std::shared_ptr<SectPx_Coord>& theQ1
			);

			void SetPar
			(
				const std::shared_ptr<SectPx_Par>& thePar
			);


			word RegObjTypeName() const override;

			//- override virtual functions from geoMap abstract class 

			Pnt2d CalcCoord() const override;

			//- override virtual functions from parent abstract class 

			Standard_Integer NbChildren() const override;

			Standard_Boolean IsComplete() const override;

			Standard_Boolean HasChildren() const override;

			Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Par>& thePar
			) const override;

			void RemoveThisFromChilds() const override;

			void AddThisToChilds() const override;

			void AddThisToChild
			(
				const std::shared_ptr<SectPx_Par>& thePar
			) const override;

			void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Par>& thePar
			) const override;

			std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;


			static std::shared_ptr<GeoMap_LinearInterpl> 
				MakeLinearInterpl
				(
					const std::shared_ptr<SectPx_Registry>& theReg
				);
		};
	}
}

#endif // !_SectPx_GeoMap_LinearInterpl_Header
