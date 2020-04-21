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

		HydStatic_GM0Curve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_GM0Curve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_GM0Curve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);


		Standard_Real GM0() const;

		Standard_Real Heel() const;
	};
}

#endif // !_HydStatic_GM0Curve_Header
