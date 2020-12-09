#pragma once
#ifndef _HydStatic_DynStbGraph_Header
#define _HydStatic_DynStbGraph_Header

#include <HydStatic_StbGraph.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_hArmCurve;	

	class HydStatic_DynStbGraph
		: public HydStatic_StbGraph
	{

		/*Private Data*/

		std::shared_ptr<HydStatic_hArmCurve> theHeelArm_;		

	public:

		TnbHydStatic_EXPORT HydStatic_DynStbGraph();


		const auto& HeelArm() const
		{
			return theHeelArm_;
		}

		auto& ChangeHeelArm()
		{
			return theHeelArm_;
		}

		void SetHeelArm
		(
			const std::shared_ptr<HydStatic_hArmCurve>&& theArm
		)
		{
			theHeelArm_ = std::move(theArm);
		}

		
	};
}

#endif // !_HydStatic_DynStbGraph_Header
