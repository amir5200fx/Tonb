#pragma once
#ifndef _GeoSizeFun3d_Background_Header
#define _GeoSizeFun3d_Background_Header

#include <GeoSizeFun_Background.hxx>
#include <GeoSizeFun3d_BackgroundFwd.hxx>
#include <GeoSizeFun3d_nonUniform.hxx>
#include <GeoMesh3d_Background.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void GeoSizeFun3d_Background::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void GeoSizeFun3d_Background::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoSizeFun3d_Background);

#endif // !_GeoSizeFun3d_Background_Header
