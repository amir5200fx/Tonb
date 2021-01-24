#pragma once
#ifndef _SectPx_Pnt_Dangle_Header
#define _SectPx_Pnt_Dangle_Header

#include <SectPx_BndPole.hxx>
#include <SectPx_PntsFwd.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class Pole_Dangle
			: public SectPx_BndPole
		{

			/*Private Data*/

			std::shared_ptr<Pnt_Compnt> thePnt_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:


			static TnbSectPx_EXPORT const char* typeName_;

			Pole_Dangle()
			{}

			TnbSectPx_EXPORT Pole_Dangle(const std::shared_ptr<Pnt_Compnt>& thePnt);

			TnbSectPx_EXPORT Pole_Dangle
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);

			TnbSectPx_EXPORT Pole_Dangle
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);

			Standard_Boolean IsDangle() const override
			{
				return Standard_True;
			}

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::dangle;
			}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pnt>
				Pnt() const override;

			void SetPnt(const std::shared_ptr<sectPxLib::Pnt_Compnt>& thePnt)
			{
				thePnt_ = thePnt;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::Pole_Dangle);

#endif // !_SectPx_Pnt_Dangle_Header