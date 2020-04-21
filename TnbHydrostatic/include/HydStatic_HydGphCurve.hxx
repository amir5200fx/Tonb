#pragma once
#ifndef _HydStatic_HydGphCurve_Header
#define _HydStatic_HydGphCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_HydGphCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

	protected:

		HydStatic_HydGphCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_HydGphCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_HydGphCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		Standard_Real MinValue() const;

		Standard_Real MaxValue() const;

		Standard_Real Value(const Standard_Real theT) const;
	};
}

#endif // !_HydStatic_HydGphCurve_Header
