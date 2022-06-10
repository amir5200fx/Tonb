#pragma once
#ifndef _SectPx_Pole_Slave_Header
#define _SectPx_Pole_Slave_Header

#include <SectPx_PairedPole.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		// Forward Declarations
		class Pole_Master;
		class Pnt_Empty;

		class Pole_Slave
			: public SectPx_PairedPole
		{

			/*Private Data*/

			std::shared_ptr<Pole_Master> theMaster_;
			std::shared_ptr<Pnt_Empty> thePnt_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:


			static TnbSectPx_EXPORT const char* typeName_;

			Pole_Slave()
			{}

			Pole_Slave(const std::shared_ptr<Pnt_Empty>& thePnt)
				: thePnt_(thePnt)
			{}

			TnbSectPx_EXPORT Pole_Slave
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pnt_Empty>& thePnt
			);

			TnbSectPx_EXPORT Pole_Slave
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pnt_Empty>& thePnt
			);

			Standard_Boolean IsSlave() const override
			{
				return Standard_True;
			}

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::slave;
			}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pnt>
				Pnt() const override;

			const auto& Master() const
			{
				return theMaster_;
			}

			void SetMaster(const std::shared_ptr<Pole_Master>& theMaster)
			{
				theMaster_ = theMaster;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::Pole_Slave);

#endif // !_SectPx_Pole_Slave_Header