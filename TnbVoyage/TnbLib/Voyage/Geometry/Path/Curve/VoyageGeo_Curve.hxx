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

		TnbVoyage_EXPORT Pnt2d Value(const Standard_Real x) const override;
		TnbVoyage_EXPORT Dir2d CalcNormal(const Standard_Real) const override;

		TnbVoyage_EXPORT Pnt2d Start() const override;
		TnbVoyage_EXPORT Pnt2d End() const override;

		TnbVoyage_EXPORT std::vector<Standard_Real> 
			Discrete
			(
				const std::shared_ptr<Geo2d_MetricPrcsrAnIso>&, 
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			) const override;

	};
}

#endif // !_VoyageGeo_Curve_Header
