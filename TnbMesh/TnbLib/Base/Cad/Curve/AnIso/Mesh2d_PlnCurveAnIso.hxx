#pragma once
#ifndef _Mesh2d_PlnCurveAnIso_Header
#define _Mesh2d_PlnCurveAnIso_Header

#include <Mesh_PlnCurve.hxx>
#include <Mesh2d_PlnCurveAnIsoFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveAnIso::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveAnIso::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Mesh2d_PlnCurveAnIso_Header
