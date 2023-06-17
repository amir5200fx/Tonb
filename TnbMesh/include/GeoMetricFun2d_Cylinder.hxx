#pragma once
#ifndef _GeoMetricFun2d_Cylinder_Header
#define _GeoMetricFun2d_Cylinder_Header

#include <GeoMetricFun2d_Uniform.hxx>

#include <Standard_Handle.hxx>

// Forward Declarations [6/13/2023 Payvand]
class Geom_CylindricalSurface;

namespace tnbLib
{

	class GeoMetricFun2d_Cylinder
		: public GeoMetricFun2d_Uniform
	{

		/*Private Data*/

		Handle(Geom_CylindricalSurface) theSurface_;


		// Private functions and operators [6/13/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

		TnbMesh_EXPORT void CalcMetric();

	protected:

		// default constructor [6/13/2023 Payvand]

		GeoMetricFun2d_Cylinder()
		{}

	public:


		// constructors [6/13/2023 Payvand]

		GeoMetricFun2d_Cylinder
		(
			const Handle(Geom_CylindricalSurface)& theSurface,
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_Uniform(0, "cylindericalMetric", theDomain)
			, theSurface_(theSurface)
		{
			CalcMetric();
		}

		GeoMetricFun2d_Cylinder
		(
			const Handle(Geom_CylindricalSurface)& theSurface,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_Uniform(0, "planeMetric", std::move(theDomain))
			, theSurface_(theSurface)
		{
			CalcMetric();
		}

		GeoMetricFun2d_Cylinder
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_CylindricalSurface)& theSurface,
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_Uniform(theIndex, theName, theDomain)
			, theSurface_(theSurface)
		{
			CalcMetric();
		}

		GeoMetricFun2d_Cylinder
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_CylindricalSurface)& theSurface,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_Uniform(theIndex, theName, std::move(theDomain))
			, theSurface_(theSurface)
		{
			CalcMetric();
		}


		// Public functions and operators [6/13/2023 Payvand]

		const auto& Geometry() const
		{
			return theSurface_;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMetricFun2d_Cylinder);

#endif // !_GeoMetricFun2d_Cylinder_Header
