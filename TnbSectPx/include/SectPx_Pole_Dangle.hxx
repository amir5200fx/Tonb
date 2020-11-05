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


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		public:


			static const char* typeName_;

			Pole_Dangle()
			{}

			Pole_Dangle(const std::shared_ptr<Pnt_Compnt>& thePnt);

			Pole_Dangle
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);

			Pole_Dangle
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);

			Standard_Boolean IsDangle() const override
			{
				return Standard_True;
			}

			word RegObjTypeName() const override;

			Pnt2d Coord() const override;

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::dangle;
			}

			std::shared_ptr<SectPx_Pnt>
				Pnt() const override;

			void SetPnt(const std::shared_ptr<sectPxLib::Pnt_Compnt>& thePnt)
			{
				thePnt_ = thePnt;
			}
		};
	}
}

#endif // !_SectPx_Pnt_Dangle_Header