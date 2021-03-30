#pragma once
#ifndef _ISC08_GustWind_Header
#define _ISC08_GustWind_Header

#include <Global_Done.hxx>
#include <ISC08_Parameter.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_DynStbGraph;

	class ISC08_GustWind
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<HydStatic_DynStbGraph> theStability_;

		isc08Lib::Phi thePhi0_;
		isc08Lib::Phi thePhi1_;
		isc08Lib::Lw theLw2_;

		isc08Lib::Phi thePhi2_;

	public:

		TnbISC08_EXPORT ISC08_GustWind();

		TnbISC08_EXPORT ISC08_GustWind
		(
			const std::shared_ptr<HydStatic_DynStbGraph>& theStability,
			const isc08Lib::Phi& thePhi0,
			const isc08Lib::Phi& thePhi1,
			const isc08Lib::Lw& theLw2
		);


		const auto& Stability() const
		{
			return theStability_;
		}

		auto& ChangeStability()
		{
			return theStability_;
		}

		const auto& Phi0() const
		{
			return thePhi0_;
		}

		auto& ChangePhi0()
		{
			return thePhi0_;
		}

		const auto& Phi1() const
		{
			return thePhi1_;
		}

		auto& ChangePhi1()
		{
			return thePhi1_;
		}

		const auto& Lw2() const
		{
			return theLw2_;
		}

		auto& Lw2()
		{
			return theLw2_;
		}

		const auto& Phi2() const
		{
			return thePhi2_;
		}

		TnbISC08_EXPORT void Perform();

		void LoadStability
		(
			const std::shared_ptr<HydStatic_DynStbGraph>& theStb
		)
		{
			theStability_ = theStb;
		}

		void SetPhi0
		(
			const isc08Lib::Phi&& theAng
		)
		{
			thePhi0_ = std::move(theAng);
		}

		void SetPhi1
		(
			const isc08Lib::Phi&& theAng
		)
		{
			thePhi1_ = std::move(theAng);
		}

		void SetLw2
		(
			const isc08Lib::Lw&& theLw2
		)
		{
			theLw2_ = std::move(theLw2);
		}
	};
}

#endif // !_ISC08_GustWind_Header
