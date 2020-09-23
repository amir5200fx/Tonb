#pragma once
#ifndef _SectPx_Pole_Master_Header
#define _SectPx_Pole_Master_Header

#include <SectPx_PairedPole.hxx>
#include <SectPx_PntsFwd.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class Pole_Master
			: public SectPx_PairedPole
		{

			/*Private Data*/

			std::shared_ptr<Pnt_Compnt> thePnt_;

		public:


			static const char* typeName_;

			Pole_Master()
			{}

			Pole_Master(const std::shared_ptr<Pnt_Compnt>& thePnt)
				: thePnt_(thePnt)
			{}

			Pole_Master
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);

			Pole_Master
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);


			word RegObjTypeName() const override;

			Pnt2d Coord() const override;

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::master;
			}

			std::shared_ptr<SectPx_Pnt>
				Pnt() const override;

			Standard_Boolean IsMaster() const override
			{
				return Standard_True;
			}

			void SetPnt(const std::shared_ptr<sectPxLib::Pnt_Compnt>& thePnt)
			{
				thePnt_ = thePnt;
			}
		};
	}
}

#endif // !_SectPx_Pole_Master_Header