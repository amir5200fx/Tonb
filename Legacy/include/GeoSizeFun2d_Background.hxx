#pragma once
#ifndef _GeoSizeFun2d_Background_Header
#define _GeoSizeFun2d_Background_Header

#include <GeoSizeFun_Background.hxx>
#include <GeoSizeFun2d_BackgroundFwd.hxx>
#include <GeoSizeFun2d_nonUniform.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void GeoSizeFun2d_Background::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void GeoSizeFun2d_Background::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoSizeFun2d_Background);

#endif // !_GeoSizeFun2d_Background_Header
