#pragma once
#ifndef _HydStatic_rArmCurve_GGv_Header
#define _HydStatic_rArmCurve_GGv_Header

#include <HydStatic_Entity.hxx>
#include <HydStatic_rArmCurve_EntityM.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		// Forward Declarations
		template<class ArmCurve>
		class rArmCurve_Cmpt;

		class rArmCurve_LDT;

		R_ARMCURVE_ENTITYM(rArmCurve_GGv, rArmCurve_LDT)
	}
}

#endif // !_HydStatic_rArmCurve_GGv_Header
