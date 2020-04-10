#pragma once
#ifndef _HydStatic_ArmCurve_Header
#define _HydStatic_ArmCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_ArmCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

	protected:

		HydStatic_ArmCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_ArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_ArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:


	};
}

#endif // !_HydStatic_ArmCurve_Header
