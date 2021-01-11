#pragma once
#ifndef _SectPx_TopoSegment_Header
#define _SectPx_TopoSegment_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_BndPole;

	class SectPx_TopoSegment
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::shared_ptr<SectPx_BndPole> thePole0_;
		std::shared_ptr<SectPx_BndPole> thePole1_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		SectPx_TopoSegment()
		{}

		TnbSectPx_EXPORT SectPx_TopoSegment
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		TnbSectPx_EXPORT SectPx_TopoSegment
		(
			const std::shared_ptr<SectPx_BndPole>& thePole0,
			const std::shared_ptr<SectPx_BndPole>& thePole1
		);

		TnbSectPx_EXPORT SectPx_TopoSegment
		(
			std::shared_ptr<SectPx_BndPole>&& thePole0,
			std::shared_ptr<SectPx_BndPole>&& thePole1
		);

		TnbSectPx_EXPORT SectPx_TopoSegment
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<SectPx_BndPole>& thePole0,
			const std::shared_ptr<SectPx_BndPole>& thePole1
		);

		TnbSectPx_EXPORT SectPx_TopoSegment
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<SectPx_BndPole>&& thePole0,
			std::shared_ptr<SectPx_BndPole>&& thePole1
		);


		const auto& Pole0() const
		{
			return thePole0_;
		}

		const auto& Pole1() const
		{
			return thePole1_;
		}

		void SetPole0(const std::shared_ptr<SectPx_BndPole>& thePole)
		{
			thePole0_ = thePole;
		}

		void SetPole1(const std::shared_ptr<SectPx_BndPole>& thePole)
		{
			thePole1_ = thePole;
		}

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsTopoSegment() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_TopoSegment);

#endif // !_SectPx_TopoSegment_Header
