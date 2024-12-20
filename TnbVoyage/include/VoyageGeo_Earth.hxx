#pragma once
#ifndef _VoyageGeo_Earth_Header
#define _VoyageGeo_Earth_Header

#include <Voyage_Module.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/27/2023 Payvand]
	class Cad_Shape;
	class Cad_GeomSurface;

	class VoyageGeo_Earth
	{

		/*Private Data*/

		std::shared_ptr<Cad_Shape> theGeometry_;

	public:

		static TnbVoyage_EXPORT const Standard_Real Radius;

		// default constructor [7/27/2023 Payvand]

		TnbVoyage_EXPORT VoyageGeo_Earth();

		// constructors [7/27/2023 Payvand]


		// Public functions and operators [7/27/2023 Payvand]

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		TnbVoyage_EXPORT std::shared_ptr<Cad_GeomSurface> Surface() const;
		TnbVoyage_EXPORT std::pair<Standard_Real, Standard_Real> Periods() const;

		TnbVoyage_EXPORT std::shared_ptr<Geo2d_MetricFunction> GetMetrics() const;

	};
}

#endif // !_VoyageGeo_Earth_Header
