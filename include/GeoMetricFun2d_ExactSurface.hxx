#pragma once
#ifndef _GeoMetricFun2d_ExactSurface_Header
#define _GeoMetricFun2d_ExactSurface_Header

#include <GeoMetricFun2d_nonUniform.hxx>

#include <Standard_Handle.hxx>

// Forward Declarations [12/24/2021 Amir]
class Geom_Surface;

namespace tnbLib
{

	class GeoMetricFun2d_ExactSurface
		: public GeoMetricFun2d_nonUniform
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;

		// Private functions and operators [12/24/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);


		// default constructor [12/25/2021 Amir]

		GeoMetricFun2d_ExactSurface()
		{}

	public:

		static TnbMesh_EXPORT Standard_Real Epsilon;

		// constructors [12/24/2021 Amir]

		explicit GeoMetricFun2d_ExactSurface
		(
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_nonUniform(0, "surfaceMetric", theDomain)
		{}

		explicit GeoMetricFun2d_ExactSurface
		(
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_nonUniform(0, "surfaceMetric", std::move(theDomain))
		{}

		GeoMetricFun2d_ExactSurface
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_nonUniform(theIndex, theName, theDomain)
		{}

		GeoMetricFun2d_ExactSurface
		(
			const Standard_Integer theIndex,
			const word& theName,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_nonUniform(theIndex, theName, std::move(theDomain))
		{}

		GeoMetricFun2d_ExactSurface
		(
			const Handle(Geom_Surface)& theSurface,
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_nonUniform(0, "surfaceMetric", theDomain)
			, theSurface_(theSurface)
		{}

		GeoMetricFun2d_ExactSurface
		(
			const Handle(Geom_Surface)& theSurface,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_nonUniform(0, "surfaceMetric", std::move(theDomain))
			, theSurface_(theSurface)
		{}

		GeoMetricFun2d_ExactSurface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Surface)& theSurface,
			const Entity2d_Box& theDomain
		)
			: GeoMetricFun2d_nonUniform(theIndex, theName, theDomain)
			, theSurface_(theSurface)
		{}

		GeoMetricFun2d_ExactSurface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Surface)& theSurface,
			Entity2d_Box&& theDomain
		)
			: GeoMetricFun2d_nonUniform(theIndex, theName, std::move(theDomain))
			, theSurface_(theSurface)
		{}

		// Public functions and operators [12/24/2021 Amir]


		const auto& Geometry() const
		{
			return theSurface_;
		}

		void SetGeometry(const Handle(Geom_Surface)& theGeometry)
		{
			theSurface_ = theGeometry;
		}

		void SetGeometry(Handle(Geom_Surface)&& theGeometry)
		{
			theSurface_ = std::move(theGeometry);
		}

		TnbMesh_EXPORT Entity2d_Metric1 Value(const Pnt2d& theCoord) const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMetricFun2d_ExactSurface);

#endif // !_GeoMetricFun2d_ExactSurface_Header
