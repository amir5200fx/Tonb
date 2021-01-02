#pragma once
#ifndef _SectPx_GeoMap_Intersection_Header
#define _SectPx_GeoMap_Intersection_Header

#include <SectPx_GeoMap.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;
	class SectPx_Par;

	namespace sectPxLib
	{

		class GeoMap_Intersection
			: public SectPx_GeoMap
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Coord> theQ0_;
			std::shared_ptr<SectPx_Coord> theQ1_;

			Dir2d theDir0_;
			Dir2d theDir1_;

			std::weak_ptr<SectPx_Par> theAngle0_;
			std::weak_ptr<SectPx_Par> theAngle1_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			template<class... _Types>
			GeoMap_Intersection(_Types&&... _Args)
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

			const auto& Dir0() const
			{
				return theDir0_;
			}

			auto& ChangeDir0()
			{
				return theDir0_;
			}

			const auto& Dir1() const
			{
				return theDir1_;
			}

			auto& ChangeDir1()
			{
				return theDir1_;
			}

			const auto& Angle0() const
			{
				return theAngle0_;
			}

			const auto& Angle1() const
			{
				return theAngle1_;
			}

			TnbSectPx_EXPORT void SetQ0
			(
				const std::shared_ptr<SectPx_Coord>& theQ0
			);

			TnbSectPx_EXPORT void SetQ1
			(
				const std::shared_ptr<SectPx_Coord>& theQ1
			);

			TnbSectPx_EXPORT void SetDir0(const Dir2d& theD0);

			TnbSectPx_EXPORT void SetDir1(const Dir2d& theD1);

			TnbSectPx_EXPORT void SetAngle0
			(
				const std::shared_ptr<SectPx_Par>& theAngle
			);

			TnbSectPx_EXPORT void SetAngle1
			(
				const std::shared_ptr<SectPx_Par>& theAngle
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

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
				RetrieveChildren() const override;

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

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::GeoMap_Intersection);

#endif // !_SectPx_GeoMap_Intersection_Header
