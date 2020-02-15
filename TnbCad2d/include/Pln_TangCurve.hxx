#pragma once
#ifndef _Pln_TangCurve_Header
#define _Pln_TangCurve_Header

#include <Pln_Curve.hxx>

namespace tnbLib
{

	class Pln_TangCurve
		: public Pln_Curve
	{

		/*Private Data*/

	public:

		Pln_TangCurve()
		{}

		Pln_TangCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		)
			: Pln_Curve(theIndex, theGeom)
		{}

		Pln_TangCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		)
			: Pln_Curve(theGeom)
		{}

		Pln_TangCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		)
			: Pln_Curve(theIndex, theName, theGeom)
		{}

		Standard_Boolean IsTangential() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_Pln_TangCurve_Header
