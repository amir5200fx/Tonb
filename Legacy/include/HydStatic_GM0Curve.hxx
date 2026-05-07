#pragma once
#ifndef _HydStatic_GM0Curve_Header
#define _HydStatic_GM0Curve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_GM0Curve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

	public:

		TnbHydStatic_EXPORT HydStatic_GM0Curve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		/*TnbHydStatic_EXPORT HydStatic_GM0Curve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);*/

		TnbHydStatic_EXPORT HydStatic_GM0Curve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);


		TnbHydStatic_EXPORT Standard_Real GM0() const;

		TnbHydStatic_EXPORT Standard_Real Heel() const;
	};
}

#endif // !_HydStatic_GM0Curve_Header
