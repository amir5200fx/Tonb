#pragma once
#ifndef _SectPx_ProfileShape_Header
#define _SectPx_ProfileShape_Header

#include <SectPx_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_BndPole;

	class SectPx_ProfileShape
		: public SectPx_Shape
	{

		/*Private Data*/

		std::shared_ptr<SectPx_BndPole> thePole0_;
		std::shared_ptr<SectPx_BndPole> thePole1_;

	public:

		SectPx_ProfileShape()
		{}

		SectPx_ProfileShape(const Standard_Integer theIndex, const word& theName);

		SectPx_ProfileShape(const std::shared_ptr<SectPx_BndPole>& theP0, const std::shared_ptr<SectPx_BndPole>& theP1);

		SectPx_ProfileShape(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<SectPx_BndPole>& theP0, const std::shared_ptr<SectPx_BndPole>& theP1);


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


		Standard_Boolean IsProfile() const override;
	};
}

#endif // !_SectPx_ProfileShape_Header
