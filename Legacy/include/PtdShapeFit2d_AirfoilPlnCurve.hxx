#pragma once
#ifndef _PtdShapeFit2d_AirfoilPlnCurve_Header
#define _PtdShapeFit2d_AirfoilPlnCurve_Header

#include <Pln_Curve.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilPlnCurve
		: public Pln_Curve
	{

		/*Private Data*/

	protected:

		// default constructor [4/28/2023 Payvand]

		PtdShapeFit2d_AirfoilPlnCurve()
		{}

		// constructors [4/28/2023 Payvand]

		PtdShapeFit2d_AirfoilPlnCurve(const Handle(Geom2d_Curve)& theGeom)
			: Pln_Curve(theGeom)
		{}

		PtdShapeFit2d_AirfoilPlnCurve(Handle(Geom2d_Curve)&& theGeom)
			: Pln_Curve(std::move(theGeom))
		{}

		PtdShapeFit2d_AirfoilPlnCurve
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		)
			: Pln_Curve(theIndex, theName, theGeom)
		{}

		PtdShapeFit2d_AirfoilPlnCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theGeom
		)
			: Pln_Curve(theIndex, theName, std::move(theGeom))
		{}

	public:

		// Public functions and operators [4/28/2023 Payvand]

		virtual Standard_Boolean IsLowerSurface() const { return Standard_False; }
		virtual Standard_Boolean IsUpperSurface() const { return Standard_False; }
		virtual Standard_Boolean IsLeadingEdgeSurface() const { return Standard_False; }

	};

}

#endif // !_PtdShapeFit2d_AirfoilPlnCurve_Header
