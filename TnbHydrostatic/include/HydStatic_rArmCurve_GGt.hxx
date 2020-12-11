#pragma once
#ifndef _HydStatic_rArmCurve_GGt_Header
#define _HydStatic_rArmCurve_GGt_Header

#include <HydStatic_Entity.hxx>
#include <HydStatic_rArmCurve_EntityM.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		// Forward Declarations
		template<class ArmCurve>
		class rArmCurve_Cmpt;

		class rArmCurve_LDV;

		R_ARMCURVE_ENTITYM(rArmCurve_GGt, rArmCurve_LDV)
	}
}

#endif // !_HydStatic_rArmCurve_GGt_Header
