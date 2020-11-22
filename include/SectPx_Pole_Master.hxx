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


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		public:


			static TnbSectPx_EXPORT const char* typeName_;

			Pole_Master()
			{}

			Pole_Master(const std::shared_ptr<Pnt_Compnt>& thePnt)
				: thePnt_(thePnt)
			{}

			TnbSectPx_EXPORT Pole_Master
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);

			TnbSectPx_EXPORT Pole_Master
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pnt_Compnt>& thePnt
			);


			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::master;
			}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pnt>
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

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::Pole_Master);

#endif // !_SectPx_Pole_Master_Header