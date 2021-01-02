#pragma once
#ifndef _SectPx_GeoMap_LinearInterpl_Header
#define _SectPx_GeoMap_LinearInterpl_Header

#include <SectPx_GeoMap.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;
	class SectPx_Par;
	class SectPx_FrameRegistry;

	namespace sectPxLib
	{

		class GeoMap_LinearInterpl
			: public SectPx_GeoMap
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Coord> theQ0_;
			std::shared_ptr<SectPx_Coord> theQ1_;

			std::weak_ptr<SectPx_Par> thePar_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:

			static TnbSectPx_EXPORT const char* typeName_;

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

			TnbSectPx_EXPORT void SetQ0
			(
				const std::shared_ptr<SectPx_Coord>& theQ0
			);

			TnbSectPx_EXPORT void SetQ1
			(
				const std::shared_ptr<SectPx_Coord>& theQ1
			);

			TnbSectPx_EXPORT void SetPar
			(
				const std::shared_ptr<SectPx_Par>& thePar
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

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;


			static TnbSectPx_EXPORT std::shared_ptr<GeoMap_LinearInterpl>
				MakeLinearInterpl
				(
					const std::shared_ptr<SectPx_FrameRegistry>& theReg
				);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::GeoMap_LinearInterpl);

#endif // !_SectPx_GeoMap_LinearInterpl_Header
