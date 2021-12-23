#pragma once
#ifndef _GeoMetricFun_nonUniform_Header
#define _GeoMetricFun_nonUniform_Header

#include <Geo_MetricFunction.hxx>

namespace tnbLib
{

	template<class Point>
	class GeoMetricFun_nonUniform
		: public Geo_MetricFunction<Point>
	{

		/*Private Data*/


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo_MetricFunction<Point>>(*this);
		}

	protected:

		GeoMetricFun_nonUniform()
		{}

		GeoMetricFun_nonUniform
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Geo_MetricFunction<Point>(theIndex, theName)
		{}

		GeoMetricFun_nonUniform
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Entity_Box<Point>& theBoundingBox
		)
			: Geo_MetricFunction<Point>(theIndex, theName, theBoundingBox)
		{}


	public:

		//- public functions and operators


	};
}

#include <GeoMetricFun2d_nonUniform.hxx>
#include <GeoMetricFun3d_nonUniform.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoMetricFun2d_nonUniform);
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoMetricFun3d_nonUniform);

#endif // !_GeoMetricFun_nonUniform_Header