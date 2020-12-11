#pragma once
#ifndef _HydStatic_GZ_Header
#define _HydStatic_GZ_Header

#include <Global_Done.hxx>
#include <Marine_VesselParam_KG.hxx>
#include <Marine_VesselParam_DISPV.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrossCurves;
	class HydStatic_rArmCurve;

	class HydStatic_GZ
		: public Global_Done
	{

		/*Private Data*/

		marineLib::KG theKg_;
		marineLib::DISPV theDispv_;

		std::shared_ptr<HydStatic_CrossCurves> theCrossCurves_;

		std::shared_ptr<HydStatic_rArmCurve> theRightingArm_;

		//- private functions and operators

		auto& ChangeKG()
		{
			return theKg_;
		}

		auto& ChangeRightingArm()
		{
			return theRightingArm_;
		}

	public:

		TnbHydStatic_EXPORT HydStatic_GZ();

		TnbHydStatic_EXPORT HydStatic_GZ
		(
			const std::shared_ptr<HydStatic_CrossCurves>& theCrossCurves,
			const Standard_Real theKG,
			const Standard_Real theDispv
		);

		const auto& KG() const
		{
			return theKg_;
		}

		const auto& DISPV() const
		{
			return theDispv_;
		}

		const auto& CrossCurves() const
		{
			return theCrossCurves_;
		}

		const auto& RightingArm() const
		{
			return theRightingArm_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadCrossCurves
		(
			const std::shared_ptr<HydStatic_CrossCurves>& theCrossCurves
		)
		{
			theCrossCurves_ = theCrossCurves;
		}

		TnbHydStatic_EXPORT void SetKG(const Standard_Real theKG);
	};
}

#endif // !_HydStatic_GZ_Header
