#pragma once
#ifndef _ShapePx_TopoSectSegment_Header
#define _ShapePx_TopoSectSegment_Header

#include <ShapePx_TopoSectEntity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSectPole;

	class ShapePx_TopoSectSegment
		: public ShapePx_TopoSectEntity
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_TopoSectPole> thePole0_;
		std::shared_ptr<ShapePx_TopoSectPole> thePole1_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);


	public:

		//- default constructor

		ShapePx_TopoSectSegment()
		{}

		//- constructors

		ShapePx_TopoSectSegment
		(
			const std::shared_ptr<ShapePx_TopoSectPole>& thePole0,
			const std::shared_ptr<ShapePx_TopoSectPole>& thePole1
		)
			: thePole0_(thePole0)
			, thePole1_(thePole1)
		{}

		ShapePx_TopoSectSegment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<ShapePx_TopoSectPole>& thePole0, 
			const std::shared_ptr<ShapePx_TopoSectPole>& thePole1
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, thePole0_(thePole0)
			, thePole1_(thePole1)
		{}

		ShapePx_TopoSectSegment
		(
			std::shared_ptr<ShapePx_TopoSectPole>&& thePole0, 
			std::shared_ptr<ShapePx_TopoSectPole>&& thePole1
		)
			: thePole0_(std::move(thePole0))
			, thePole1_(std::move(thePole1))
		{}

		ShapePx_TopoSectSegment
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::shared_ptr<ShapePx_TopoSectPole>&& thePole0,
			std::shared_ptr<ShapePx_TopoSectPole>&& thePole1
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, thePole0_(std::move(thePole0))
			, thePole1_(std::move(thePole1))
		{}


		//- public functions and operators

		const auto& Pole0() const
		{
			return thePole0_;
		}

		const auto& Pole1() const
		{
			return thePole1_;
		}

		void SetPole0(const std::shared_ptr<ShapePx_TopoSectPole>& thePole)
		{
			thePole0_ = thePole;
		}

		void SetPole0(std::shared_ptr<ShapePx_TopoSectPole>&& thePole)
		{
			thePole0_ = std::move(thePole);
		}

		void SetPole1(const std::shared_ptr<ShapePx_TopoSectPole>& thePole)
		{
			thePole1_ = thePole;
		}

		void SetPole1(std::shared_ptr<ShapePx_TopoSectPole>&& thePole)
		{
			thePole1_ = std::move(thePole);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_TopoSectSegment);

#endif // !_ShapePx_TopoSectSegment_Header
