#pragma once
#ifndef _SectPx_Pnt_Corner_Header
#define _SectPx_Pnt_Corner_Header

#include <SectPx_InterPole.hxx>
#include <SectPx_Pole_CornerAdaptor.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;

	namespace sectPxLib
	{

		class Pole_Corner
			: public SectPx_InterPole
			, public SectPx_Pole_CornerAdaptor
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Pnt> thePnt_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:


			static TnbSectPx_EXPORT const char* typeName_;

			Pole_Corner()
			{}

			Pole_Corner
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			)
				: thePnt_(thePnt)
			{}

			TnbSectPx_EXPORT Pole_Corner
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

			TnbSectPx_EXPORT Pole_Corner
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			Standard_Boolean IsCorner() const override
			{
				return Standard_True;
			}

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::corner;
			}

			std::shared_ptr<SectPx_Pnt>
				Pnt() const override
			{
				return thePnt_;
			}

			void SetPnt(const std::shared_ptr<SectPx_Pnt>& thePnt)
			{
				thePnt_ = thePnt;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::Pole_Corner);

#endif // !_SectPx_Pnt_Corner_Header