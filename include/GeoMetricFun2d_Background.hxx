#pragma once
#ifndef _GeoMetricFun2d_Background_Header
#define _GeoMetricFun2d_Background_Header

#include <GeoMetricFun_Background.hxx>
#include <GeoMesh2d_MetricBackground.hxx>

namespace tnbLib
{

	typedef GeoMetricFun_Background<GeoMesh2d_MetricBackground>
		GeoMetricFun2d_Background;


	template<>
	template<>
	void GeoMetricFun2d_Background::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	void GeoMetricFun2d_Background::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMetricFun2d_Background);

#endif // !_GeoMetricFun2d_Background_Header