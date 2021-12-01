#pragma once
#ifndef _Aft2d_BoundaryOfPlane_Info_Header
#define _Aft2d_BoundaryOfPlane_Info_Header

#include <Aft_BoundaryOfPlane_Info.hxx>
#include <Aft2d_BoundaryOfPlane_InfoFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlane_Info::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlane_Info::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_BoundaryOfPlane_Info_Header
