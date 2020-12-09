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

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_BnjCurve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT Standard_Boolean IsIntersect
		(
			const Standard_Real theT
		) const;

		TnbHydStatic_EXPORT Standard_Real A0() const;

		TnbHydStatic_EXPORT Standard_Real A1() const;

		TnbHydStatic_EXPORT Standard_Real Value
		(
			const Standard_Real theT
		) const;

	};
}

#endif // !_HydStatic_BnjCurve_Header
