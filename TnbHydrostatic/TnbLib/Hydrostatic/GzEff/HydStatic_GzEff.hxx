#pragma once
#ifndef _HydStatic_GzEff_Header
#define _HydStatic_GzEff_Header

#include <Global_Done.hxx>
#include <HydStatic_Module.hxx>
#include <HydStatic_rArmCurvesFwd.hxx>

#include <memory>

namespace tnbLib
{

	namespace hydStcLib
	{

		// Forward Declarations
		class rArmCurve_Eff;
	}

	// Forward Declarations
	class HydStatic_SolutionData_GzEff;

	class HydStatic_GzEff
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<hydStcLib::rArmCurve_Body> theBody_;
		std::shared_ptr<hydStcLib::rArmCurve_Tanks> theTanks_;

		std::shared_ptr<hydStcLib::rArmCurve_Eff> theEff_;

	public:

		//- constructor

		explicit HydStatic_GzEff(const std::shared_ptr<hydStcLib::rArmCurve_Body>& theBody)
			: theBody_(theBody)
		{}

		//- public functions and operators

		const auto& BodyGz() const
		{
			return theBody_;
		}

		const auto& TanksGz() const
		{
			return theTanks_;
		}

		const auto& GzEff() const
		{
			return theEff_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadTanksGz
		(
			const std::shared_ptr<hydStcLib::rArmCurve_Tanks>& theTanks
		)
		{
			theTanks_ = theTanks;
		}
	};
}

#endif // !_HydStatic_GzEff_Header
