#pragma once
#ifndef _HydStatic_rArmCurve_Tanks_Header
#define _HydStatic_rArmCurve_Tanks_Header

#include <HydStatic_Entity.hxx>
#include <HydStatic_rArmCurve_EntityM.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		// Forward Declarations
		template<class ArmCurve>
		class rArmCurve_Cmpt;

		class rArmCurve_FSLq;

		R_ARMCURVE_ENTITYM(rArmCurve_Tanks, rArmCurve_FSLq)

	}
}

#endif // !_HydStatic_rArmCurve_Tanks_Header
