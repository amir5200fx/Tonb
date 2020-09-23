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

		class Pole_Slave
			: public SectPx_PairedPole
		{

			/*Private Data*/

			std::shared_ptr<Pole_Master> theMaster_;

		public:


			static const char* typeName_;

			Pole_Slave()
			{}

			Pole_Slave(const std::shared_ptr<Pole_Master>& theMaster)
				: theMaster_(theMaster)
			{}

			Pole_Slave
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pole_Master>& theMaster
			);

			Pole_Slave
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pole_Master>& theMaster
			);

			Standard_Boolean IsSlave() const override
			{
				return Standard_True;
			}

			word RegObjTypeName() const override;

			Pnt2d Coord() const override;

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::slave;
			}

			std::shared_ptr<SectPx_Pnt>
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

#endif // !_SectPx_Pole_Slave_Header