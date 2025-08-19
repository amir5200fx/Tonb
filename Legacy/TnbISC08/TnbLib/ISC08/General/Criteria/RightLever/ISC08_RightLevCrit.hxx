#pragma once
#ifndef _ISC08_RightLevCrit_Header
#define _ISC08_RightLevCrit_Header

#include <Standard_TypeDef.hxx>
#include <Global_Done.hxx>
#include <Marine_VesselParam_DFLDANG.hxx>
#include <ISC08_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rArmCurve;
	class Marine_CriterionTable;
	class HydStatic_StbGraph;

	namespace marineLib { class Criterion_Standard; }

	class ISC08_RightLevCrit
		: public Global_Done
	{

		typedef marineLib::Criterion_Standard standard;

		/*Private Data*/

		std::shared_ptr<HydStatic_StbGraph> theStability_;

	public:

		static TnbISC08_EXPORT const standard PHI_25;
		static TnbISC08_EXPORT const standard PHI_30;
		static TnbISC08_EXPORT const standard PHI_40;

		static TnbISC08_EXPORT const standard PHI_UPTO_30_MRAD;
		static TnbISC08_EXPORT const standard PHI_UPTO_40_MRAD;

		static TnbISC08_EXPORT const standard PHI_30_AND_40_MRAD;

		static TnbISC08_EXPORT const standard MIN_RIGTHLEV_AT_PHI_30;

		static TnbISC08_EXPORT const standard MIN_GM0;

		TnbISC08_EXPORT ISC08_RightLevCrit();

		TnbISC08_EXPORT ISC08_RightLevCrit
		(
			const std::shared_ptr<HydStatic_StbGraph>& theGZ
		);


		const auto& Stablity() const
		{
			return theStability_;
		}

		TnbISC08_EXPORT void Perform();

		void LoadStablity
		(
			const std::shared_ptr<HydStatic_StbGraph>& theStb
		)
		{
			theStability_ = theStb;
		}

	};
}

#endif // !_ISC08_RightLevCrit_Header
