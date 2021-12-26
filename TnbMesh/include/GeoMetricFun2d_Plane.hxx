#pragma once
#ifndef _GeoMetricFun2d_Plane_Header
#define _GeoMetricFun2d_Plane_Header

#include <GeoMetricFun2d_Uniform.hxx>

#include <Standard_Handle.hxx>

// Forward Declarations [12/24/2021 Amir]
class Geom_Plane;

namespace tnbLib
{

	class GeoMetricFun2d_Plane
		: public GeoMetricFun2d_Uniform
	{

		/*Private Data*/

		Handle(Geom_Plane) theSurface_;


		// Private functions and operators [12/24/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);


		TnbMesh_EXPORT void CalcMetric();


		// default constructor [12/24/2021 Amir]

		GeoMetricFun2d_Plane()
		{}

	public:


		// constructors [12/24/2021 Amir]

		GeoMetricFun2d_Plane
		(
			const Handle(Geom_Plane)& theSurface,
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_Uniform(0, "planeMetric", theDomain)
			, theSurface_(theSurface)
		{
			CalcMetric();
		}

		GeoMetricFun2d_Plane
		(
			const Handle(Geom_Plane)& theSurface,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_Uniform(0, "planeMetric", std::move(theDomain))
			, theSurface_(theSurface)
		{
			CalcMetric();
		}

		GeoMetricFun2d_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Plane)& theSurface,
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_Uniform(theIndex, theName, theDomain)
			, theSurface_(theSurface)
		{
			CalcMetric();
		}

		GeoMetricFun2d_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Plane)& theSurface,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_Uniform(theIndex, theName, std::move(theDomain))
			, theSurface_(theSurface)
		{
			CalcMetric();
		}


		// Public functions and operators [12/24/2021 Amir]


		const auto& Geometry() const
		{
			return theSurface_;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMetricFun2d_Plane);

#endif // !_GeoMetricFun2d_Plane_Header
