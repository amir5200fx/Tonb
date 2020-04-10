#pragma once
#ifndef _HydStatic_rArmCurve_Header
#define _HydStatic_rArmCurve_Header

#include <HydStatic_ArmCurve.hxx>

namespace tnbLib
{

	class HydStatic_rArmCurve
		: public HydStatic_ArmCurve
	{

		/*Private Data*/

	public:

		HydStatic_rArmCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_rArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);
	};
}

#endif // !_HydStatic_rArmCurve_Header
