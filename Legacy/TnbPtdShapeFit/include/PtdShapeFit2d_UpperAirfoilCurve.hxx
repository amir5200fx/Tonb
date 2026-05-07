#pragma once
#ifndef _PtdShapeFit2d_UpperAirfoilCurve_Header
#define _PtdShapeFit2d_UpperAirfoilCurve_Header

#include <PtdShapeFit2d_AirfoilPlnCurve.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_UpperAirfoilCurve
		: public PtdShapeFit2d_AirfoilPlnCurve
	{

		/*Private Data*/

	public:

		// default constructor [4/28/2023 Payvand]

		PtdShapeFit2d_UpperAirfoilCurve()
		{}

		// constructors [4/28/2023 Payvand]

		PtdShapeFit2d_UpperAirfoilCurve(const Handle(Geom2d_Curve)& theGeom)
			: PtdShapeFit2d_AirfoilPlnCurve(theGeom)
		{}

		PtdShapeFit2d_UpperAirfoilCurve(Handle(Geom2d_Curve) && theGeom)
			: PtdShapeFit2d_AirfoilPlnCurve(std::move(theGeom))
		{}

		PtdShapeFit2d_UpperAirfoilCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		)
			: PtdShapeFit2d_AirfoilPlnCurve(theIndex, theName, theGeom)
		{}

		PtdShapeFit2d_UpperAirfoilCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve) && theGeom
		)
			: PtdShapeFit2d_AirfoilPlnCurve(theIndex, theName, std::move(theGeom))
		{}


		// Public functions and operators [4/28/2023 Payvand]

		Standard_Boolean IsUpperSurface() const override { return Standard_True; }

	};
}

#endif // !_PtdShapeFit2d_UpperAirfoilCurve_Header
