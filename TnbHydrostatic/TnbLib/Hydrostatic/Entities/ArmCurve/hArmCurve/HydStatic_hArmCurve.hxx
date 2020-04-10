#pragma once
#ifndef _HydStatic_hArmCurve_Header
#define _HydStatic_hArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	class HydStatic_hArmCurve
		: public HydStatic_ArmCurve
	{

		/*Private Data*/

	public:

		HydStatic_hArmCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_hArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_hArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);
	};
}

#endif // !_HydStatic_hArmCurve_Header
