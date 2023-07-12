#pragma once
#ifndef _VoyageGeo_Curve_Header
#define _VoyageGeo_Curve_Header

#include <VoyageGeo_Path.hxx>

// Forward Declarations [7/10/2023 Payvand]
class Geom2d_Curve;

namespace tnbLib
{

	class VoyageGeo_Curve
		: public VoyageGeo_Path
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;

	public:

		// default constructor [7/10/2023 Payvand]

		// constructors [7/10/2023 Payvand]

		VoyageGeo_Curve(const Handle(Geom2d_Curve)& theGeometry)
			: theGeometry_(theGeometry)
		{}

		VoyageGeo_Curve(Handle(Geom2d_Curve)&& theGeometry)
			: theGeometry_(std::move(theGeometry))
		{}


		// Public functions and operators [7/10/2023 Payvand]

		const auto& Geometry() const { return theGeometry_; }

		Pnt2d Value(const Standard_Real x) const override;
		Dir2d CalcNormal(const Standard_Real) const override;

		Pnt2d Start() const override;
		Pnt2d End() const override;

	};
}

#endif // !_VoyageGeo_Curve_Header
