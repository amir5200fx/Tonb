#pragma once
#ifndef _HydStatic_BnjCurve_Header
#define _HydStatic_BnjCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_BnjCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

	public:

		HydStatic_BnjCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_BnjCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_BnjCurve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);

		Standard_Boolean IsIntersect
		(
			const Standard_Real theT
		) const;

		Standard_Real A0() const;

		Standard_Real A1() const;

		Standard_Real Value
		(
			const Standard_Real theT
		) const;

	};
}

#endif // !_HydStatic_BnjCurve_Header
