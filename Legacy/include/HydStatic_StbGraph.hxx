#pragma once
#ifndef _HydStatic_StbGraph_Header
#define _HydStatic_StbGraph_Header

#include <HydStatic_Entity.hxx>
#include <Marine_VesselParam_DISPV.hxx>
#include <Marine_VesselParam_KG.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rArmCurve;
	class HydStatic_GM0Curve;
	class HydStatic_DFldCurve;

	class HydStatic_StbGraph
	{

		/*Private Data*/

		marineLib::DISPV theDispv_;
		marineLib::KG theKg_;


		std::shared_ptr<HydStatic_rArmCurve> theRightingArm_;
		std::shared_ptr<HydStatic_GM0Curve> theGM0_;
		std::shared_ptr<HydStatic_DFldCurve> theDwnFlooding_;

	protected:

		TnbHydStatic_EXPORT HydStatic_StbGraph();

		
	public:

		const auto& DISPV() const
		{
			return theDispv_;
		}

		auto& ChangeDISPV()
		{
			return theDispv_;
		}

		const auto& KG() const
		{
			return theKg_;
		}

		auto& ChangeKG()
		{
			return theKg_;
		}

		const auto& RightingArm() const
		{
			return theRightingArm_;
		}

		auto& ChangeRightingArm()
		{
			return theRightingArm_;
		}

		const auto& GM0() const
		{
			return theGM0_;
		}

		auto& ChangeGM0()
		{
			return theGM0_;
		}

		const auto& DwnFlooding() const
		{
			return theDwnFlooding_;
		}

		auto& ChangeDownFlooding()
		{
			return theDwnFlooding_;
		}

		void SetDISPV
		(
			const marineLib::DISPV&& theDispv
		)
		{
			theDispv_ = std::move(theDispv);
		}

		void SetKG
		(
			const marineLib::KG&& theKg
		)
		{
			theKg_ = std::move(theKg);
		}

		void SetRightingArm
		(
			const std::shared_ptr<HydStatic_rArmCurve>&& theArm
		)
		{
			theRightingArm_ = std::move(theArm);
		}

		void SetGM0
		(
			const std::shared_ptr<HydStatic_GM0Curve>&& theGM0
		)
		{
			theGM0_ = std::move(theGM0);
		}

		void SetDownFlooding
		(
			const std::shared_ptr<HydStatic_DFldCurve>&& theDownFlooding
		)
		{
			theDwnFlooding_ = std::move(theDownFlooding);
		}
	};
}

#endif // !_HydStatic_StbGraph_Header
