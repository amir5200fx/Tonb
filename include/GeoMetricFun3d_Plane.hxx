#pragma once
#ifndef _GeoMetricFun3d_Plane_Header
#define _GeoMetricFun3d_Plane_Header

#include <GeoMetricFun2d_Plane.hxx>

namespace tnbLib
{

	class GeoMetricFun3d_Plane
		: public GeoMetricFun2d_Plane
	{

		/*Private Data*/

		// Private functions and operators [3/9/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<GeoMetricFun2d_Plane>(*this);
		}

	protected:

		// default constructor [3/9/2023 Payvand]

		GeoMetricFun3d_Plane()
		{}

	public:

		// constructors [3/9/2023 Payvand]

		GeoMetricFun3d_Plane(const Handle(Geom_Plane)& thePlane, const Entity2d_Box& theDomain)
			: GeoMetricFun2d_Plane(thePlane, theDomain)
		{}

		GeoMetricFun3d_Plane(const Handle(Geom_Plane)& thePlane, Entity2d_Box&& theDomain)
			: GeoMetricFun2d_Plane(thePlane, std::move(theDomain))
		{}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMetricFun3d_Plane);

#endif // !_GeoMetricFun3d_Plane_Header
