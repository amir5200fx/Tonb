#pragma once
#ifndef _HydStatic_CrsCurve_Header
#define _HydStatic_CrsCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_CrsCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

	public:

		HydStatic_CrsCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_CrsCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_CrsCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);


		Standard_Boolean IsIntersect(const Standard_Real theVolume) const;

		Standard_Real LeverArm0() const;

		Standard_Real LeverArm1() const;

		Standard_Real Value(const Standard_Real theVolume) const;
	};
}

#endif // !_HydStatic_CrsCurve_Header
