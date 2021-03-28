#pragma once
#ifndef _HydStatic_Equilib_Header
#define _HydStatic_Equilib_Header

#include <Global_Done.hxx>
#include <HydStatic_GzQ.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rArmCurve;
	class HydStatic_hArmCurve;
	
	namespace hydStcLib
	{
		class rArmCurve_Eff;
	}

	class HydStatic_Equilib
		: public Global_Done
	{

	public:

		typedef HydStatic_GzQ gzQ;

	private:

		/*Private Data*/


		std::shared_ptr<hydStcLib::rArmCurve_Eff> theGz_;
		std::shared_ptr<HydStatic_hArmCurve> theHeelArm_;


		std::vector<gzQ> theQs_;

	protected:

		//- default constructor

		HydStatic_Equilib()
		{}


		//- constructors

		HydStatic_Equilib
		(
			const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz
		)
			: theGz_(theGz)
		{}


		auto& ChangePoints()
		{
			return theQs_;
		}

	public:

		//- public functions and operators

		const auto& Gz() const
		{
			return theGz_;
		}

		auto& ChangeGz()
		{
			return theGz_;
		}

		const auto& HeelingArm() const
		{
			return theHeelArm_;
		}

		auto& ChangeHeelingArm()
		{
			return theHeelArm_;
		}

		const auto& Points() const
		{
			return theQs_;
		}

		void SetGz
		(
			const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theGz
		)
		{
			theGz_ = theGz;
		}

		void SetHeelingArm
		(
			const std::shared_ptr<HydStatic_hArmCurve>& theHeeling
		)
		{
			theHeelArm_ = theHeeling;
		}

	};
}

#endif // !_HydStatic_Equilib_Header
